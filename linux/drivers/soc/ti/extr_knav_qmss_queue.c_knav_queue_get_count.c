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
struct knav_queue_inst {int /*<<< orphan*/  desc_count; } ;
struct knav_queue {TYPE_1__* reg_peek; struct knav_queue_inst* inst; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry_count; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int readl_relaxed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int knav_queue_get_count(void *qhandle)
{
	struct knav_queue *qh = qhandle;
	struct knav_queue_inst *inst = qh->inst;

	return readl_relaxed(&qh->reg_peek[0].entry_count) +
		atomic_read(&inst->desc_count);
}