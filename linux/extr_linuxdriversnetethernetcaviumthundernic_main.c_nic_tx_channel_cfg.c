#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct sq_cfg_msg {size_t sq_num; scalar_t__ sqs_mode; } ;
struct nicpf {size_t* pqs_vf; size_t** vf_sqs; int /*<<< orphan*/ * vf_lmac_map; struct hw_info* hw; } ;
struct hw_info {int tl4_cnt; int bgx_cnt; int tl3_cnt; int chans_per_lmac; int chans_per_bgx; scalar_t__ tl1_per_bgx; } ;

/* Variables and functions */
 int MAX_LMAC_PER_BGX ; 
 int MAX_QUEUES_PER_QSET ; 
 int MAX_SQS_PER_VF ; 
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_HW_MAX_FRS ; 
 int NIC_PF_CHAN_0_255_TX_CFG ; 
 int NIC_PF_QSET_0_127_SQ_0_7_CFG2 ; 
 int NIC_PF_TL2_0_63_CFG ; 
 int NIC_PF_TL2_0_63_PRI ; 
 int NIC_PF_TL2_LMAC ; 
 int NIC_PF_TL3A_0_63_CFG ; 
 int NIC_PF_TL3_0_255_CFG ; 
 int NIC_PF_TL3_0_255_CHAN ; 
 int NIC_PF_TL4_0_1023_CFG ; 
 int NIC_QS_ID_SHIFT ; 
 int NIC_Q_NUM_SHIFT ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 

__attribute__((used)) static void nic_tx_channel_cfg(struct nicpf *nic, u8 vnic,
			       struct sq_cfg_msg *sq)
{
	struct hw_info *hw = nic->hw;
	u32 bgx, lmac, chan;
	u32 tl2, tl3, tl4;
	u32 rr_quantum;
	u8 sq_idx = sq->sq_num;
	u8 pqs_vnic;
	int svf;

	if (sq->sqs_mode)
		pqs_vnic = nic->pqs_vf[vnic];
	else
		pqs_vnic = vnic;

	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[pqs_vnic]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[pqs_vnic]);

	/* 24 bytes for FCS, IPG and preamble */
	rr_quantum = ((NIC_HW_MAX_FRS + 24) / 4);

	/* For 88xx 0-511 TL4 transmits via BGX0 and
	 * 512-1023 TL4s transmit via BGX1.
	 */
	if (hw->tl1_per_bgx) {
		tl4 = bgx * (hw->tl4_cnt / hw->bgx_cnt);
		if (!sq->sqs_mode) {
			tl4 += (lmac * MAX_QUEUES_PER_QSET);
		} else {
			for (svf = 0; svf < MAX_SQS_PER_VF; svf++) {
				if (nic->vf_sqs[pqs_vnic][svf] == vnic)
					break;
			}
			tl4 += (MAX_LMAC_PER_BGX * MAX_QUEUES_PER_QSET);
			tl4 += (lmac * MAX_QUEUES_PER_QSET * MAX_SQS_PER_VF);
			tl4 += (svf * MAX_QUEUES_PER_QSET);
		}
	} else {
		tl4 = (vnic * MAX_QUEUES_PER_QSET);
	}
	tl4 += sq_idx;

	tl3 = tl4 / (hw->tl4_cnt / hw->tl3_cnt);
	nic_reg_write(nic, NIC_PF_QSET_0_127_SQ_0_7_CFG2 |
		      ((u64)vnic << NIC_QS_ID_SHIFT) |
		      ((u32)sq_idx << NIC_Q_NUM_SHIFT), tl4);
	nic_reg_write(nic, NIC_PF_TL4_0_1023_CFG | (tl4 << 3),
		      ((u64)vnic << 27) | ((u32)sq_idx << 24) | rr_quantum);

	nic_reg_write(nic, NIC_PF_TL3_0_255_CFG | (tl3 << 3), rr_quantum);

	/* On 88xx 0-127 channels are for BGX0 and
	 * 127-255 channels for BGX1.
	 *
	 * On 81xx/83xx TL3_CHAN reg should be configured with channel
	 * within LMAC i.e 0-7 and not the actual channel number like on 88xx
	 */
	chan = (lmac * hw->chans_per_lmac) + (bgx * hw->chans_per_bgx);
	if (hw->tl1_per_bgx)
		nic_reg_write(nic, NIC_PF_TL3_0_255_CHAN | (tl3 << 3), chan);
	else
		nic_reg_write(nic, NIC_PF_TL3_0_255_CHAN | (tl3 << 3), 0);

	/* Enable backpressure on the channel */
	nic_reg_write(nic, NIC_PF_CHAN_0_255_TX_CFG | (chan << 3), 1);

	tl2 = tl3 >> 2;
	nic_reg_write(nic, NIC_PF_TL3A_0_63_CFG | (tl2 << 3), tl2);
	nic_reg_write(nic, NIC_PF_TL2_0_63_CFG | (tl2 << 3), rr_quantum);
	/* No priorities as of now */
	nic_reg_write(nic, NIC_PF_TL2_0_63_PRI | (tl2 << 3), 0x00);

	/* Unlike 88xx where TL2s 0-31 transmits to TL1 '0' and rest to TL1 '1'
	 * on 81xx/83xx TL2 needs to be configured to transmit to one of the
	 * possible LMACs.
	 *
	 * This register doesn't exist on 88xx.
	 */
	if (!hw->tl1_per_bgx)
		nic_reg_write(nic, NIC_PF_TL2_LMAC | (tl2 << 3),
			      lmac + (bgx * MAX_LMAC_PER_BGX));
}