#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* q; } ;
struct rq_wb {TYPE_3__ rqos; } ;
struct bdi_writeback {scalar_t__ dirty_sleep; } ;
struct TYPE_5__ {TYPE_1__* backing_dev_info; } ;
struct TYPE_4__ {struct bdi_writeback wb; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  jiffies ; 
 int time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool wb_recent_wait(struct rq_wb *rwb)
{
	struct bdi_writeback *wb = &rwb->rqos.q->backing_dev_info->wb;

	return time_before(jiffies, wb->dirty_sleep + HZ);
}