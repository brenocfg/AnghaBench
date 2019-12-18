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
struct l2t_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/ * neigh; int /*<<< orphan*/  refcnt; } ;
struct l2t_data {int /*<<< orphan*/  nfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void t3_l2e_free(struct l2t_data *d, struct l2t_entry *e)
{
	spin_lock_bh(&e->lock);
	if (atomic_read(&e->refcnt) == 0) {	/* hasn't been recycled */
		if (e->neigh) {
			neigh_release(e->neigh);
			e->neigh = NULL;
		}
	}
	spin_unlock_bh(&e->lock);
	atomic_inc(&d->nfree);
}