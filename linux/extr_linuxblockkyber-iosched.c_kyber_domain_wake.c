#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  private; } ;
typedef  TYPE_1__ wait_queue_entry_t ;
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 struct blk_mq_hw_ctx* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queue (struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kyber_domain_wake(wait_queue_entry_t *wait, unsigned mode, int flags,
			     void *key)
{
	struct blk_mq_hw_ctx *hctx = READ_ONCE(wait->private);

	list_del_init(&wait->entry);
	blk_mq_run_hw_queue(hctx, true);
	return 1;
}