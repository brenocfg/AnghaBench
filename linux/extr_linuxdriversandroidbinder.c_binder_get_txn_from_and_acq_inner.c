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
struct binder_transaction {struct binder_thread* from; } ;
struct binder_thread {int /*<<< orphan*/  proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct binder_thread* binder_get_txn_from (struct binder_transaction*) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_thread_dec_tmpref (struct binder_thread*) ; 

__attribute__((used)) static struct binder_thread *binder_get_txn_from_and_acq_inner(
		struct binder_transaction *t)
{
	struct binder_thread *from;

	from = binder_get_txn_from(t);
	if (!from)
		return NULL;
	binder_inner_proc_lock(from->proc);
	if (t->from) {
		BUG_ON(from != t->from);
		return from;
	}
	binder_inner_proc_unlock(from->proc);
	binder_thread_dec_tmpref(from);
	return NULL;
}