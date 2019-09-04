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
struct binder_transaction {int /*<<< orphan*/  lock; struct binder_thread* from; } ;
struct binder_thread {int /*<<< orphan*/  tmp_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct binder_thread *binder_get_txn_from(
		struct binder_transaction *t)
{
	struct binder_thread *from;

	spin_lock(&t->lock);
	from = t->from;
	if (from)
		atomic_inc(&from->tmp_ref);
	spin_unlock(&t->lock);
	return from;
}