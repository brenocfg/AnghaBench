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
struct binder_transaction_log_entry {int /*<<< orphan*/  debug_id_done; } ;
struct binder_transaction_log {int full; struct binder_transaction_log_entry* entry; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct binder_transaction_log_entry*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct binder_transaction_log_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static struct binder_transaction_log_entry *binder_transaction_log_add(
	struct binder_transaction_log *log)
{
	struct binder_transaction_log_entry *e;
	unsigned int cur = atomic_inc_return(&log->cur);

	if (cur >= ARRAY_SIZE(log->entry))
		log->full = true;
	e = &log->entry[cur % ARRAY_SIZE(log->entry)];
	WRITE_ONCE(e->debug_id_done, 0);
	/*
	 * write-barrier to synchronize access to e->debug_id_done.
	 * We make sure the initialized 0 value is seen before
	 * memset() other fields are zeroed by memset.
	 */
	smp_wmb();
	memset(e, 0, sizeof(*e));
	return e;
}