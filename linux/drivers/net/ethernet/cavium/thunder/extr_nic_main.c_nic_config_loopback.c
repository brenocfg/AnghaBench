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
struct set_loopback {size_t vf_id; int /*<<< orphan*/  enable; } ;
struct nicpf {size_t num_vf_en; int /*<<< orphan*/  node; int /*<<< orphan*/ * vf_lmac_map; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIC_PF_CQ_AVG_CFG ; 
 int /*<<< orphan*/  NIC_PF_RRM_AVG_CFG ; 
 int /*<<< orphan*/  bgx_lmac_internal_loopback (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nic_config_loopback(struct nicpf *nic, struct set_loopback *lbk)
{
	int bgx_idx, lmac_idx;

	if (lbk->vf_id >= nic->num_vf_en)
		return -1;

	bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lbk->vf_id]);
	lmac_idx = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lbk->vf_id]);

	bgx_lmac_internal_loopback(nic->node, bgx_idx, lmac_idx, lbk->enable);

	/* Enable moving average calculation.
	 * Keep the LVL/AVG delay to HW enforced minimum so that, not too many
	 * packets sneek in between average calculations.
	 */
	nic_reg_write(nic, NIC_PF_CQ_AVG_CFG,
		      (BIT_ULL(20) | 0x2ull << 14 | 0x1));
	nic_reg_write(nic, NIC_PF_RRM_AVG_CFG,
		      (BIT_ULL(20) | 0x3ull << 14 | 0x1));

	return 0;
}