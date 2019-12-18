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

/* Variables and functions */
 int /*<<< orphan*/  cio_work_q ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

void css_wait_for_slow_path(void)
{
	flush_workqueue(cio_work_q);
}