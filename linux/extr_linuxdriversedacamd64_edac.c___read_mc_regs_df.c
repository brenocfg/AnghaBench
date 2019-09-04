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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct amd64_umc {int /*<<< orphan*/  umc_cap_hi; int /*<<< orphan*/  ecc_ctrl; int /*<<< orphan*/  sdp_ctrl; int /*<<< orphan*/  umc_cfg; int /*<<< orphan*/  dimm_cfg; } ;
struct amd64_pvt {struct amd64_umc* umc; int /*<<< orphan*/  mc_node_id; } ;

/* Variables and functions */
 size_t NUM_UMCS ; 
 size_t UMCCH_DIMM_CFG ; 
 size_t UMCCH_ECC_CTRL ; 
 size_t UMCCH_SDP_CTRL ; 
 size_t UMCCH_UMC_CAP_HI ; 
 size_t UMCCH_UMC_CFG ; 
 int /*<<< orphan*/  amd_smn_read (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 size_t get_umc_base (size_t) ; 

__attribute__((used)) static void __read_mc_regs_df(struct amd64_pvt *pvt)
{
	u8 nid = pvt->mc_node_id;
	struct amd64_umc *umc;
	u32 i, umc_base;

	/* Read registers from each UMC */
	for (i = 0; i < NUM_UMCS; i++) {

		umc_base = get_umc_base(i);
		umc = &pvt->umc[i];

		amd_smn_read(nid, umc_base + UMCCH_DIMM_CFG, &umc->dimm_cfg);
		amd_smn_read(nid, umc_base + UMCCH_UMC_CFG, &umc->umc_cfg);
		amd_smn_read(nid, umc_base + UMCCH_SDP_CTRL, &umc->sdp_ctrl);
		amd_smn_read(nid, umc_base + UMCCH_ECC_CTRL, &umc->ecc_ctrl);
		amd_smn_read(nid, umc_base + UMCCH_UMC_CAP_HI, &umc->umc_cap_hi);
	}
}