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
struct deadline_data {int /*<<< orphan*/ * fifo_list; int /*<<< orphan*/  dispatch; } ;
struct blk_mq_hw_ctx {TYPE_2__* queue; } ;
struct TYPE_4__ {TYPE_1__* elevator; } ;
struct TYPE_3__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dd_has_work(struct blk_mq_hw_ctx *hctx)
{
	struct deadline_data *dd = hctx->queue->elevator->elevator_data;

	return !list_empty_careful(&dd->dispatch) ||
		!list_empty_careful(&dd->fifo_list[0]) ||
		!list_empty_careful(&dd->fifo_list[1]);
}