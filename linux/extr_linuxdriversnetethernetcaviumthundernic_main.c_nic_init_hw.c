#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_6__ {int lenerr_en; scalar_t__ hdr_sl; scalar_t__ rx_hdr; scalar_t__ maxlen; scalar_t__ minlen; } ;
struct nicpf {TYPE_3__ pkind; TYPE_2__* hw; TYPE_1__* pdev; } ;
struct TYPE_5__ {int bgx_cnt; } ;
struct TYPE_4__ {scalar_t__ subsystem_device; } ;

/* Variables and functions */
 int BGX0_BLOCK ; 
 int BGX1_BLOCK ; 
 scalar_t__ ETH_FCS_LEN ; 
 int ETH_P_8021Q ; 
 int ETYPE_ALG_VLAN_STRIP ; 
 int NICPF_CLK_PER_INT_TICK ; 
 int NICPF_CQM_MIN_DROP_LEVEL ; 
 scalar_t__ NIC_HW_MAX_FRS ; 
 int /*<<< orphan*/  NIC_HW_MIN_FRS ; 
 int NIC_MAX_PKIND ; 
 int NIC_PF_BP_CFG ; 
 int NIC_PF_CFG ; 
 int NIC_PF_CQM_CFG ; 
 int NIC_PF_INTFX_SEND_CFG ; 
 int NIC_PF_INTF_0_1_BP_CFG ; 
 int NIC_PF_INTF_0_1_SEND_CFG ; 
 int NIC_PF_INTR_TIMER_CFG ; 
 int NIC_PF_PKIND_0_15_CFG ; 
 int NIC_PF_RX_ETYPE_0_7 ; 
 int NIC_TNS_BYPASS_MODE ; 
 scalar_t__ PCI_SUBSYS_DEVID_88XX_NIC_PF ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int nic_reg_read (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 
 int /*<<< orphan*/  nic_set_tx_pkt_pad (struct nicpf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nic_init_hw(struct nicpf *nic)
{
	int i;
	u64 cqm_cfg;

	/* Enable NIC HW block */
	nic_reg_write(nic, NIC_PF_CFG, 0x3);

	/* Enable backpressure */
	nic_reg_write(nic, NIC_PF_BP_CFG, (1ULL << 6) | 0x03);

	/* TNS and TNS bypass modes are present only on 88xx
	 * Also offset of this CSR has changed in 81xx and 83xx.
	 */
	if (nic->pdev->subsystem_device == PCI_SUBSYS_DEVID_88XX_NIC_PF) {
		/* Disable TNS mode on both interfaces */
		nic_reg_write(nic, NIC_PF_INTF_0_1_SEND_CFG,
			      (NIC_TNS_BYPASS_MODE << 7) |
			      BGX0_BLOCK | (1ULL << 16));
		nic_reg_write(nic, NIC_PF_INTF_0_1_SEND_CFG | (1 << 8),
			      (NIC_TNS_BYPASS_MODE << 7) |
			      BGX1_BLOCK | (1ULL << 16));
	} else {
		/* Configure timestamp generation timeout to 10us */
		for (i = 0; i < nic->hw->bgx_cnt; i++)
			nic_reg_write(nic, NIC_PF_INTFX_SEND_CFG | (i << 3),
				      (1ULL << 16));
	}

	nic_reg_write(nic, NIC_PF_INTF_0_1_BP_CFG,
		      (1ULL << 63) | BGX0_BLOCK);
	nic_reg_write(nic, NIC_PF_INTF_0_1_BP_CFG + (1 << 8),
		      (1ULL << 63) | BGX1_BLOCK);

	/* PKIND configuration */
	nic->pkind.minlen = 0;
	nic->pkind.maxlen = NIC_HW_MAX_FRS + VLAN_ETH_HLEN + ETH_FCS_LEN + 4;
	nic->pkind.lenerr_en = 1;
	nic->pkind.rx_hdr = 0;
	nic->pkind.hdr_sl = 0;

	for (i = 0; i < NIC_MAX_PKIND; i++)
		nic_reg_write(nic, NIC_PF_PKIND_0_15_CFG | (i << 3),
			      *(u64 *)&nic->pkind);

	nic_set_tx_pkt_pad(nic, NIC_HW_MIN_FRS);

	/* Timer config */
	nic_reg_write(nic, NIC_PF_INTR_TIMER_CFG, NICPF_CLK_PER_INT_TICK);

	/* Enable VLAN ethertype matching and stripping */
	nic_reg_write(nic, NIC_PF_RX_ETYPE_0_7,
		      (2 << 19) | (ETYPE_ALG_VLAN_STRIP << 16) | ETH_P_8021Q);

	/* Check if HW expected value is higher (could be in future chips) */
	cqm_cfg = nic_reg_read(nic, NIC_PF_CQM_CFG);
	if (cqm_cfg < NICPF_CQM_MIN_DROP_LEVEL)
		nic_reg_write(nic, NIC_PF_CQM_CFG, NICPF_CQM_MIN_DROP_LEVEL);
}