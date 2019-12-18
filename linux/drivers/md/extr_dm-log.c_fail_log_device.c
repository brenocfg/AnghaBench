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
struct log_c {int log_dev_failed; TYPE_1__* ti; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fail_log_device(struct log_c *lc)
{
	if (lc->log_dev_failed)
		return;

	lc->log_dev_failed = 1;
	dm_table_event(lc->ti->table);
}