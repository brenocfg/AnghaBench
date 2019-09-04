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
typedef  size_t u32 ;
struct amd64_umc {int dimm_cfg; int umc_cfg; int sdp_ctrl; int ecc_ctrl; int umc_cap_hi; } ;
struct amd64_pvt {scalar_t__ dram_type; size_t dhar; int /*<<< orphan*/  mc_node_id; struct amd64_umc* umc; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ MEM_LRDDR4 ; 
 size_t NUM_UMCS ; 
 size_t UMCCH_ADDR_CFG ; 
 size_t UMCCH_ECC_BAD_SYMBOL ; 
 size_t UMCCH_UMC_CAP ; 
 int /*<<< orphan*/  amd_smn_read (int /*<<< orphan*/ ,size_t,size_t*) ; 
 int /*<<< orphan*/  debug_display_dimm_sizes_df (struct amd64_pvt*,size_t) ; 
 int dhar_base (struct amd64_pvt*) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,size_t,...) ; 
 size_t get_umc_base (size_t) ; 

__attribute__((used)) static void __dump_misc_regs_df(struct amd64_pvt *pvt)
{
	struct amd64_umc *umc;
	u32 i, tmp, umc_base;

	for (i = 0; i < NUM_UMCS; i++) {
		umc_base = get_umc_base(i);
		umc = &pvt->umc[i];

		edac_dbg(1, "UMC%d DIMM cfg: 0x%x\n", i, umc->dimm_cfg);
		edac_dbg(1, "UMC%d UMC cfg: 0x%x\n", i, umc->umc_cfg);
		edac_dbg(1, "UMC%d SDP ctrl: 0x%x\n", i, umc->sdp_ctrl);
		edac_dbg(1, "UMC%d ECC ctrl: 0x%x\n", i, umc->ecc_ctrl);

		amd_smn_read(pvt->mc_node_id, umc_base + UMCCH_ECC_BAD_SYMBOL, &tmp);
		edac_dbg(1, "UMC%d ECC bad symbol: 0x%x\n", i, tmp);

		amd_smn_read(pvt->mc_node_id, umc_base + UMCCH_UMC_CAP, &tmp);
		edac_dbg(1, "UMC%d UMC cap: 0x%x\n", i, tmp);
		edac_dbg(1, "UMC%d UMC cap high: 0x%x\n", i, umc->umc_cap_hi);

		edac_dbg(1, "UMC%d ECC capable: %s, ChipKill ECC capable: %s\n",
				i, (umc->umc_cap_hi & BIT(30)) ? "yes" : "no",
				    (umc->umc_cap_hi & BIT(31)) ? "yes" : "no");
		edac_dbg(1, "UMC%d All DIMMs support ECC: %s\n",
				i, (umc->umc_cfg & BIT(12)) ? "yes" : "no");
		edac_dbg(1, "UMC%d x4 DIMMs present: %s\n",
				i, (umc->dimm_cfg & BIT(6)) ? "yes" : "no");
		edac_dbg(1, "UMC%d x16 DIMMs present: %s\n",
				i, (umc->dimm_cfg & BIT(7)) ? "yes" : "no");

		if (pvt->dram_type == MEM_LRDDR4) {
			amd_smn_read(pvt->mc_node_id, umc_base + UMCCH_ADDR_CFG, &tmp);
			edac_dbg(1, "UMC%d LRDIMM %dx rank multiply\n",
					i, 1 << ((tmp >> 4) & 0x3));
		}

		debug_display_dimm_sizes_df(pvt, i);
	}

	edac_dbg(1, "F0x104 (DRAM Hole Address): 0x%08x, base: 0x%08x\n",
		 pvt->dhar, dhar_base(pvt));
}