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
typedef  int u64 ;
typedef  int u16 ;
struct rvu {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int BLKADDR_CPT0 ; 
 int BLKADDR_NIX0 ; 
 int BLKADDR_NPA ; 
 int BLKADDR_NPC ; 
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 int BLKADDR_SSO ; 
 int BLKADDR_SSOW ; 
 int BLKADDR_TIM ; 
#define  BLKTYPE_CPT 134 
#define  BLKTYPE_NIX 133 
#define  BLKTYPE_NPA 132 
#define  BLKTYPE_NPC 131 
#define  BLKTYPE_SSO 130 
#define  BLKTYPE_SSOW 129 
#define  BLKTYPE_TIM 128 
 int ENODEV ; 
 int RVU_PFVF_FUNC_MASK ; 
 int RVU_PRIV_HWVFX_CPT0_CFG ; 
 int RVU_PRIV_HWVFX_NIX0_CFG ; 
 int RVU_PRIV_PFX_CPT0_CFG ; 
 int RVU_PRIV_PFX_NIX0_CFG ; 
 scalar_t__ is_block_implemented (int /*<<< orphan*/ ,int) ; 
 int rvu_get_hwvf (struct rvu*,int) ; 
 int rvu_get_pf (int) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int) ; 

int rvu_get_blkaddr(struct rvu *rvu, int blktype, u16 pcifunc)
{
	int devnum, blkaddr = -ENODEV;
	u64 cfg, reg;
	bool is_pf;

	switch (blktype) {
	case BLKTYPE_NPC:
		blkaddr = BLKADDR_NPC;
		goto exit;
	case BLKTYPE_NPA:
		blkaddr = BLKADDR_NPA;
		goto exit;
	case BLKTYPE_NIX:
		/* For now assume NIX0 */
		if (!pcifunc) {
			blkaddr = BLKADDR_NIX0;
			goto exit;
		}
		break;
	case BLKTYPE_SSO:
		blkaddr = BLKADDR_SSO;
		goto exit;
	case BLKTYPE_SSOW:
		blkaddr = BLKADDR_SSOW;
		goto exit;
	case BLKTYPE_TIM:
		blkaddr = BLKADDR_TIM;
		goto exit;
	case BLKTYPE_CPT:
		/* For now assume CPT0 */
		if (!pcifunc) {
			blkaddr = BLKADDR_CPT0;
			goto exit;
		}
		break;
	}

	/* Check if this is a RVU PF or VF */
	if (pcifunc & RVU_PFVF_FUNC_MASK) {
		is_pf = false;
		devnum = rvu_get_hwvf(rvu, pcifunc);
	} else {
		is_pf = true;
		devnum = rvu_get_pf(pcifunc);
	}

	/* Check if the 'pcifunc' has a NIX LF from 'BLKADDR_NIX0' */
	if (blktype == BLKTYPE_NIX) {
		reg = is_pf ? RVU_PRIV_PFX_NIX0_CFG : RVU_PRIV_HWVFX_NIX0_CFG;
		cfg = rvu_read64(rvu, BLKADDR_RVUM, reg | (devnum << 16));
		if (cfg)
			blkaddr = BLKADDR_NIX0;
	}

	/* Check if the 'pcifunc' has a CPT LF from 'BLKADDR_CPT0' */
	if (blktype == BLKTYPE_CPT) {
		reg = is_pf ? RVU_PRIV_PFX_CPT0_CFG : RVU_PRIV_HWVFX_CPT0_CFG;
		cfg = rvu_read64(rvu, BLKADDR_RVUM, reg | (devnum << 16));
		if (cfg)
			blkaddr = BLKADDR_CPT0;
	}

exit:
	if (is_block_implemented(rvu->hw, blkaddr))
		return blkaddr;
	return -ENODEV;
}