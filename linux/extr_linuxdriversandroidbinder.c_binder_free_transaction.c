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
struct binder_transaction {TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/ * transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_STAT_TRANSACTION ; 
 int /*<<< orphan*/  binder_stats_deleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct binder_transaction*) ; 

__attribute__((used)) static void binder_free_transaction(struct binder_transaction *t)
{
	if (t->buffer)
		t->buffer->transaction = NULL;
	kfree(t);
	binder_stats_deleted(BINDER_STAT_TRANSACTION);
}