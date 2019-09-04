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
typedef  int /*<<< orphan*/  uint32_t ;
struct binder_transaction {int flags; int /*<<< orphan*/  debug_id; TYPE_1__* buffer; } ;
struct TYPE_2__ {scalar_t__ target_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_DEAD_TRANSACTION ; 
 int TF_ONE_WAY ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  binder_free_transaction (struct binder_transaction*) ; 
 int /*<<< orphan*/  binder_send_failed_reply (struct binder_transaction*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void binder_cleanup_transaction(struct binder_transaction *t,
				       const char *reason,
				       uint32_t error_code)
{
	if (t->buffer->target_node && !(t->flags & TF_ONE_WAY)) {
		binder_send_failed_reply(t, error_code);
	} else {
		binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
			"undelivered transaction %d, %s\n",
			t->debug_id, reason);
		binder_free_transaction(t);
	}
}