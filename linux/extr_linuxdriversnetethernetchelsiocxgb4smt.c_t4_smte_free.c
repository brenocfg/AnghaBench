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
struct smt_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMT_STATE_UNUSED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void t4_smte_free(struct smt_entry *e)
{
	spin_lock_bh(&e->lock);
	if (atomic_read(&e->refcnt) == 0) {  /* hasn't been recycled */
		e->state = SMT_STATE_UNUSED;
	}
	spin_unlock_bh(&e->lock);
}