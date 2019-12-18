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
struct bm_rcr_entry {int dummy; } ;
struct bm_rcr {int busy; struct bm_rcr_entry* cursor; int /*<<< orphan*/  available; } ;
struct bm_portal {struct bm_rcr rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dpaa_zero (struct bm_rcr_entry*) ; 

__attribute__((used)) static inline struct bm_rcr_entry *bm_rcr_start(struct bm_portal *portal)
{
	struct bm_rcr *rcr = &portal->rcr;

	DPAA_ASSERT(!rcr->busy);
	if (!rcr->available)
		return NULL;
#ifdef CONFIG_FSL_DPAA_CHECKING
	rcr->busy = 1;
#endif
	dpaa_zero(rcr->cursor);
	return rcr->cursor;
}