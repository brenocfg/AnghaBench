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
typedef  int u32 ;
struct bman_portal {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int BM_PIRQ_RCRI ; 
 int /*<<< orphan*/  BM_REG_ISR ; 
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  bm_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bm_rcr_cce_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bm_rcr_set_ithresh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 poll_portal_slow(struct bman_portal *p, u32 is)
{
	u32 ret = is;

	if (is & BM_PIRQ_RCRI) {
		bm_rcr_cce_update(&p->p);
		bm_rcr_set_ithresh(&p->p, 0);
		bm_out(&p->p, BM_REG_ISR, BM_PIRQ_RCRI);
		is &= ~BM_PIRQ_RCRI;
	}

	/* There should be no status register bits left undefined */
	DPAA_ASSERT(!is);
	return ret;
}