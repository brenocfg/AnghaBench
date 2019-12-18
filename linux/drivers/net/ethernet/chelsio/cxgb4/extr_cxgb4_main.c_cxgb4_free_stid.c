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
struct tid_info {unsigned int sftid_base; unsigned int nstids; int v6_stids_in_use; int /*<<< orphan*/  stid_lock; int /*<<< orphan*/  sftids_in_use; scalar_t__ stids_in_use; TYPE_1__* stid_tab; int /*<<< orphan*/  stid_bmap; scalar_t__ stid_base; scalar_t__ nsftids; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgb4_free_stid(struct tid_info *t, unsigned int stid, int family)
{
	/* Is it a server filter TID? */
	if (t->nsftids && (stid >= t->sftid_base)) {
		stid -= t->sftid_base;
		stid += t->nstids;
	} else {
		stid -= t->stid_base;
	}

	spin_lock_bh(&t->stid_lock);
	if (family == PF_INET)
		__clear_bit(stid, t->stid_bmap);
	else
		bitmap_release_region(t->stid_bmap, stid, 1);
	t->stid_tab[stid].data = NULL;
	if (stid < t->nstids) {
		if (family == PF_INET6) {
			t->stids_in_use -= 2;
			t->v6_stids_in_use -= 2;
		} else {
			t->stids_in_use--;
		}
	} else {
		t->sftids_in_use--;
	}

	spin_unlock_bh(&t->stid_lock);
}