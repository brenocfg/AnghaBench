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
typedef  int u8 ;
typedef  int u32 ;
struct bm_rcr {int ci; int ithresh; int pmode; int cmode; scalar_t__ busy; scalar_t__ available; int /*<<< orphan*/  vbit; scalar_t__ ring; scalar_t__ cursor; } ;
struct TYPE_2__ {scalar_t__ ce; } ;
struct bm_portal {TYPE_1__ addr; struct bm_rcr rcr; } ;
typedef  enum bm_rcr_pmode { ____Placeholder_bm_rcr_pmode } bm_rcr_pmode ;
typedef  enum bm_rcr_cmode { ____Placeholder_bm_rcr_cmode } bm_rcr_cmode ;

/* Variables and functions */
 scalar_t__ BM_CL_RCR ; 
 int BM_RCR_SIZE ; 
 int /*<<< orphan*/  BM_RCR_VERB_VBIT ; 
 int /*<<< orphan*/  BM_REG_CFG ; 
 int /*<<< orphan*/  BM_REG_RCR_CI_CINH ; 
 int /*<<< orphan*/  BM_REG_RCR_ITR ; 
 int /*<<< orphan*/  BM_REG_RCR_PI_CINH ; 
 int bm_in (struct bm_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_out (struct bm_portal*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dpaa_cyc_diff (int,int,int) ; 

__attribute__((used)) static int bm_rcr_init(struct bm_portal *portal, enum bm_rcr_pmode pmode,
		       enum bm_rcr_cmode cmode)
{
	struct bm_rcr *rcr = &portal->rcr;
	u32 cfg;
	u8 pi;

	rcr->ring = portal->addr.ce + BM_CL_RCR;
	rcr->ci = bm_in(portal, BM_REG_RCR_CI_CINH) & (BM_RCR_SIZE - 1);
	pi = bm_in(portal, BM_REG_RCR_PI_CINH) & (BM_RCR_SIZE - 1);
	rcr->cursor = rcr->ring + pi;
	rcr->vbit = (bm_in(portal, BM_REG_RCR_PI_CINH) & BM_RCR_SIZE) ?
		BM_RCR_VERB_VBIT : 0;
	rcr->available = BM_RCR_SIZE - 1
		- dpaa_cyc_diff(BM_RCR_SIZE, rcr->ci, pi);
	rcr->ithresh = bm_in(portal, BM_REG_RCR_ITR);
#ifdef CONFIG_FSL_DPAA_CHECKING
	rcr->busy = 0;
	rcr->pmode = pmode;
	rcr->cmode = cmode;
#endif
	cfg = (bm_in(portal, BM_REG_CFG) & 0xffffffe0)
		| (pmode & 0x3); /* BCSP_CFG::RPM */
	bm_out(portal, BM_REG_CFG, cfg);
	return 0;
}