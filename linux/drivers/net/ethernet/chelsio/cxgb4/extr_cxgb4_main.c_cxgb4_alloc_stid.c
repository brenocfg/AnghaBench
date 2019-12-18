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
struct tid_info {int nstids; int v6_stids_in_use; int /*<<< orphan*/  stid_lock; scalar_t__ stids_in_use; scalar_t__ stid_base; TYPE_1__* stid_tab; int /*<<< orphan*/  stid_bmap; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int,int) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cxgb4_alloc_stid(struct tid_info *t, int family, void *data)
{
	int stid;

	spin_lock_bh(&t->stid_lock);
	if (family == PF_INET) {
		stid = find_first_zero_bit(t->stid_bmap, t->nstids);
		if (stid < t->nstids)
			__set_bit(stid, t->stid_bmap);
		else
			stid = -1;
	} else {
		stid = bitmap_find_free_region(t->stid_bmap, t->nstids, 1);
		if (stid < 0)
			stid = -1;
	}
	if (stid >= 0) {
		t->stid_tab[stid].data = data;
		stid += t->stid_base;
		/* IPv6 requires max of 520 bits or 16 cells in TCAM
		 * This is equivalent to 4 TIDs. With CLIP enabled it
		 * needs 2 TIDs.
		 */
		if (family == PF_INET6) {
			t->stids_in_use += 2;
			t->v6_stids_in_use += 2;
		} else {
			t->stids_in_use++;
		}
	}
	spin_unlock_bh(&t->stid_lock);
	return stid;
}