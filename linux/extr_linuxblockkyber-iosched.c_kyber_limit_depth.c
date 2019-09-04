#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kyber_queue_data {int /*<<< orphan*/  async_depth; } ;
struct blk_mq_alloc_data {int /*<<< orphan*/  shallow_depth; TYPE_2__* q; } ;
struct TYPE_4__ {TYPE_1__* elevator; } ;
struct TYPE_3__ {struct kyber_queue_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  op_is_sync (unsigned int) ; 

__attribute__((used)) static void kyber_limit_depth(unsigned int op, struct blk_mq_alloc_data *data)
{
	/*
	 * We use the scheduler tags as per-hardware queue queueing tokens.
	 * Async requests can be limited at this stage.
	 */
	if (!op_is_sync(op)) {
		struct kyber_queue_data *kqd = data->q->elevator->elevator_data;

		data->shallow_depth = kqd->async_depth;
	}
}