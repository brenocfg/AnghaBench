#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct rvu_pfvf {int dummy; } ;
struct rvu_hwinfo {int total_pfs; int total_vfs; int max_vfs_per_pf; struct rvu_block* block; } ;
struct TYPE_2__ {int max; int /*<<< orphan*/  bmap; } ;
struct rvu_block {size_t addr; int lfshift; int multislot; void* fn_map; TYPE_1__ lf; int /*<<< orphan*/  name; int /*<<< orphan*/  lfreset_reg; int /*<<< orphan*/  msixcfg_reg; int /*<<< orphan*/  lfcfg_reg; int /*<<< orphan*/  vf_lfcnt_reg; int /*<<< orphan*/  pf_lfcnt_reg; int /*<<< orphan*/  lookup_reg; int /*<<< orphan*/  type; int /*<<< orphan*/  implemented; } ;
struct rvu {int /*<<< orphan*/  dev; int /*<<< orphan*/  rsrc_lock; void* hwvf; void* pf; struct rvu_hwinfo* hw; } ;

/* Variables and functions */
 size_t BLKADDR_CPT0 ; 
 size_t BLKADDR_NIX0 ; 
 size_t BLKADDR_NPA ; 
 size_t BLKADDR_RVUM ; 
 size_t BLKADDR_SSO ; 
 size_t BLKADDR_SSOW ; 
 size_t BLKADDR_TIM ; 
 int /*<<< orphan*/  BLKTYPE_CPT ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int /*<<< orphan*/  BLKTYPE_NPA ; 
 int /*<<< orphan*/  BLKTYPE_SSO ; 
 int /*<<< orphan*/  BLKTYPE_SSOW ; 
 int /*<<< orphan*/  BLKTYPE_TIM ; 
 int BLK_COUNT ; 
 int /*<<< orphan*/  CPT_AF_CONSTANTS0 ; 
 int /*<<< orphan*/  CPT_AF_LF_RST ; 
 int /*<<< orphan*/  CPT_AF_RVU_LF_CFG_DEBUG ; 
 int /*<<< orphan*/  CPT_PRIV_LFX_CFG ; 
 int /*<<< orphan*/  CPT_PRIV_LFX_INT_CFG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NIX_AF_CONST2 ; 
 int /*<<< orphan*/  NIX_AF_LF_RST ; 
 int /*<<< orphan*/  NIX_AF_RVU_LF_CFG_DEBUG ; 
 int /*<<< orphan*/  NIX_PRIV_LFX_CFG ; 
 int /*<<< orphan*/  NIX_PRIV_LFX_INT_CFG ; 
 int /*<<< orphan*/  NPA_AF_CONST ; 
 int /*<<< orphan*/  NPA_AF_LF_RST ; 
 int /*<<< orphan*/  NPA_AF_RVU_LF_CFG_DEBUG ; 
 int /*<<< orphan*/  NPA_PRIV_LFX_CFG ; 
 int /*<<< orphan*/  NPA_PRIV_LFX_INT_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_CONST ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_CPT0_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_NIX0_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_NPA_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_SSOW_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_SSO_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_HWVFX_TIM_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_CPT0_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_NIX0_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_NPA_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_SSOW_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_SSO_CFG ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_TIM_CFG ; 
 int /*<<< orphan*/  SSOW_AF_LF_HWS_RST ; 
 int /*<<< orphan*/  SSOW_AF_RVU_LF_HWS_CFG_DEBUG ; 
 int /*<<< orphan*/  SSOW_PRIV_LFX_HWS_CFG ; 
 int /*<<< orphan*/  SSOW_PRIV_LFX_HWS_INT_CFG ; 
 int /*<<< orphan*/  SSO_AF_CONST ; 
 int /*<<< orphan*/  SSO_AF_LF_HWGRP_RST ; 
 int /*<<< orphan*/  SSO_AF_RVU_LF_CFG_DEBUG ; 
 int /*<<< orphan*/  SSO_PRIV_LFX_HWGRP_CFG ; 
 int /*<<< orphan*/  SSO_PRIV_LFX_HWGRP_INT_CFG ; 
 int /*<<< orphan*/  TIM_AF_CONST ; 
 int /*<<< orphan*/  TIM_AF_LF_RST ; 
 int /*<<< orphan*/  TIM_AF_RVU_LF_CFG_DEBUG ; 
 int /*<<< orphan*/  TIM_PRIV_LFX_CFG ; 
 int /*<<< orphan*/  TIM_PRIV_LFX_INT_CFG ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int rvu_alloc_bitmap (TYPE_1__*) ; 
 int /*<<< orphan*/  rvu_cgx_exit (struct rvu*) ; 
 int rvu_cgx_init (struct rvu*) ; 
 int rvu_nix_init (struct rvu*) ; 
 int rvu_npa_init (struct rvu*) ; 
 int rvu_npc_init (struct rvu*) ; 
 int rvu_read64 (struct rvu*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_scan_block (struct rvu*,struct rvu_block*) ; 
 int rvu_setup_msix_resources (struct rvu*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rvu_setup_hw_resources(struct rvu *rvu)
{
	struct rvu_hwinfo *hw = rvu->hw;
	struct rvu_block *block;
	int blkid, err;
	u64 cfg;

	/* Get HW supported max RVU PF & VF count */
	cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_CONST);
	hw->total_pfs = (cfg >> 32) & 0xFF;
	hw->total_vfs = (cfg >> 20) & 0xFFF;
	hw->max_vfs_per_pf = (cfg >> 40) & 0xFF;

	/* Init NPA LF's bitmap */
	block = &hw->block[BLKADDR_NPA];
	if (!block->implemented)
		goto nix;
	cfg = rvu_read64(rvu, BLKADDR_NPA, NPA_AF_CONST);
	block->lf.max = (cfg >> 16) & 0xFFF;
	block->addr = BLKADDR_NPA;
	block->type = BLKTYPE_NPA;
	block->lfshift = 8;
	block->lookup_reg = NPA_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_NPA_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_NPA_CFG;
	block->lfcfg_reg = NPA_PRIV_LFX_CFG;
	block->msixcfg_reg = NPA_PRIV_LFX_INT_CFG;
	block->lfreset_reg = NPA_AF_LF_RST;
	sprintf(block->name, "NPA");
	err = rvu_alloc_bitmap(&block->lf);
	if (err)
		return err;

nix:
	/* Init NIX LF's bitmap */
	block = &hw->block[BLKADDR_NIX0];
	if (!block->implemented)
		goto sso;
	cfg = rvu_read64(rvu, BLKADDR_NIX0, NIX_AF_CONST2);
	block->lf.max = cfg & 0xFFF;
	block->addr = BLKADDR_NIX0;
	block->type = BLKTYPE_NIX;
	block->lfshift = 8;
	block->lookup_reg = NIX_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_NIX0_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_NIX0_CFG;
	block->lfcfg_reg = NIX_PRIV_LFX_CFG;
	block->msixcfg_reg = NIX_PRIV_LFX_INT_CFG;
	block->lfreset_reg = NIX_AF_LF_RST;
	sprintf(block->name, "NIX");
	err = rvu_alloc_bitmap(&block->lf);
	if (err)
		return err;

sso:
	/* Init SSO group's bitmap */
	block = &hw->block[BLKADDR_SSO];
	if (!block->implemented)
		goto ssow;
	cfg = rvu_read64(rvu, BLKADDR_SSO, SSO_AF_CONST);
	block->lf.max = cfg & 0xFFFF;
	block->addr = BLKADDR_SSO;
	block->type = BLKTYPE_SSO;
	block->multislot = true;
	block->lfshift = 3;
	block->lookup_reg = SSO_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_SSO_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_SSO_CFG;
	block->lfcfg_reg = SSO_PRIV_LFX_HWGRP_CFG;
	block->msixcfg_reg = SSO_PRIV_LFX_HWGRP_INT_CFG;
	block->lfreset_reg = SSO_AF_LF_HWGRP_RST;
	sprintf(block->name, "SSO GROUP");
	err = rvu_alloc_bitmap(&block->lf);
	if (err)
		return err;

ssow:
	/* Init SSO workslot's bitmap */
	block = &hw->block[BLKADDR_SSOW];
	if (!block->implemented)
		goto tim;
	block->lf.max = (cfg >> 56) & 0xFF;
	block->addr = BLKADDR_SSOW;
	block->type = BLKTYPE_SSOW;
	block->multislot = true;
	block->lfshift = 3;
	block->lookup_reg = SSOW_AF_RVU_LF_HWS_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_SSOW_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_SSOW_CFG;
	block->lfcfg_reg = SSOW_PRIV_LFX_HWS_CFG;
	block->msixcfg_reg = SSOW_PRIV_LFX_HWS_INT_CFG;
	block->lfreset_reg = SSOW_AF_LF_HWS_RST;
	sprintf(block->name, "SSOWS");
	err = rvu_alloc_bitmap(&block->lf);
	if (err)
		return err;

tim:
	/* Init TIM LF's bitmap */
	block = &hw->block[BLKADDR_TIM];
	if (!block->implemented)
		goto cpt;
	cfg = rvu_read64(rvu, BLKADDR_TIM, TIM_AF_CONST);
	block->lf.max = cfg & 0xFFFF;
	block->addr = BLKADDR_TIM;
	block->type = BLKTYPE_TIM;
	block->multislot = true;
	block->lfshift = 3;
	block->lookup_reg = TIM_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_TIM_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_TIM_CFG;
	block->lfcfg_reg = TIM_PRIV_LFX_CFG;
	block->msixcfg_reg = TIM_PRIV_LFX_INT_CFG;
	block->lfreset_reg = TIM_AF_LF_RST;
	sprintf(block->name, "TIM");
	err = rvu_alloc_bitmap(&block->lf);
	if (err)
		return err;

cpt:
	/* Init CPT LF's bitmap */
	block = &hw->block[BLKADDR_CPT0];
	if (!block->implemented)
		goto init;
	cfg = rvu_read64(rvu, BLKADDR_CPT0, CPT_AF_CONSTANTS0);
	block->lf.max = cfg & 0xFF;
	block->addr = BLKADDR_CPT0;
	block->type = BLKTYPE_CPT;
	block->multislot = true;
	block->lfshift = 3;
	block->lookup_reg = CPT_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_CPT0_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_CPT0_CFG;
	block->lfcfg_reg = CPT_PRIV_LFX_CFG;
	block->msixcfg_reg = CPT_PRIV_LFX_INT_CFG;
	block->lfreset_reg = CPT_AF_LF_RST;
	sprintf(block->name, "CPT");
	err = rvu_alloc_bitmap(&block->lf);
	if (err)
		return err;

init:
	/* Allocate memory for PFVF data */
	rvu->pf = devm_kcalloc(rvu->dev, hw->total_pfs,
			       sizeof(struct rvu_pfvf), GFP_KERNEL);
	if (!rvu->pf)
		return -ENOMEM;

	rvu->hwvf = devm_kcalloc(rvu->dev, hw->total_vfs,
				 sizeof(struct rvu_pfvf), GFP_KERNEL);
	if (!rvu->hwvf)
		return -ENOMEM;

	mutex_init(&rvu->rsrc_lock);

	err = rvu_setup_msix_resources(rvu);
	if (err)
		return err;

	for (blkid = 0; blkid < BLK_COUNT; blkid++) {
		block = &hw->block[blkid];
		if (!block->lf.bmap)
			continue;

		/* Allocate memory for block LF/slot to pcifunc mapping info */
		block->fn_map = devm_kcalloc(rvu->dev, block->lf.max,
					     sizeof(u16), GFP_KERNEL);
		if (!block->fn_map)
			return -ENOMEM;

		/* Scan all blocks to check if low level firmware has
		 * already provisioned any of the resources to a PF/VF.
		 */
		rvu_scan_block(rvu, block);
	}

	err = rvu_npc_init(rvu);
	if (err)
		goto exit;

	err = rvu_cgx_init(rvu);
	if (err)
		goto exit;

	err = rvu_npa_init(rvu);
	if (err)
		goto cgx_err;

	err = rvu_nix_init(rvu);
	if (err)
		goto cgx_err;

	return 0;

cgx_err:
	rvu_cgx_exit(rvu);
exit:
	return err;
}