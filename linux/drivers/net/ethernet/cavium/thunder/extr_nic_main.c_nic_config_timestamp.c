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
typedef  int u8 ;
typedef  int u64 ;
struct set_ptp {scalar_t__ enable; } ;
struct pkind_cfg {int hdr_sl; int maxlen; } ;
struct nicpf {int num_vf_en; int /*<<< orphan*/  node; int /*<<< orphan*/ * vf_lmac_map; } ;

/* Variables and functions */
 int ETH_P_1588 ; 
 int ETH_P_8021Q ; 
 int ETYPE_ALG_ENDPARSE ; 
 int ETYPE_ALG_SKIP ; 
 int MAX_LMAC_PER_BGX ; 
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_PF_PKIND_0_15_CFG ; 
 int NIC_PF_RX_ETYPE_0_7 ; 
 int /*<<< orphan*/  bgx_config_timestamping (int /*<<< orphan*/ ,int,int,int) ; 
 int nic_reg_read (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 

__attribute__((used)) static void nic_config_timestamp(struct nicpf *nic, int vf, struct set_ptp *ptp)
{
	struct pkind_cfg *pkind;
	u8 lmac, bgx_idx;
	u64 pkind_val, pkind_idx;

	if (vf >= nic->num_vf_en)
		return;

	bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	pkind_idx = lmac + bgx_idx * MAX_LMAC_PER_BGX;
	pkind_val = nic_reg_read(nic, NIC_PF_PKIND_0_15_CFG | (pkind_idx << 3));
	pkind = (struct pkind_cfg *)&pkind_val;

	if (ptp->enable && !pkind->hdr_sl) {
		/* Skiplen to exclude 8byte timestamp while parsing pkt
		 * If not configured, will result in L2 errors.
		 */
		pkind->hdr_sl = 4;
		/* Adjust max packet length allowed */
		pkind->maxlen += (pkind->hdr_sl * 2);
		bgx_config_timestamping(nic->node, bgx_idx, lmac, true);
		nic_reg_write(nic, NIC_PF_RX_ETYPE_0_7 | (1 << 3),
			      (ETYPE_ALG_ENDPARSE << 16) | ETH_P_1588);
	} else if (!ptp->enable && pkind->hdr_sl) {
		pkind->maxlen -= (pkind->hdr_sl * 2);
		pkind->hdr_sl = 0;
		bgx_config_timestamping(nic->node, bgx_idx, lmac, false);
		nic_reg_write(nic, NIC_PF_RX_ETYPE_0_7 | (1 << 3),
			      (ETYPE_ALG_SKIP << 16) | ETH_P_8021Q);
	}

	nic_reg_write(nic, NIC_PF_PKIND_0_15_CFG | (pkind_idx << 3), pkind_val);
}