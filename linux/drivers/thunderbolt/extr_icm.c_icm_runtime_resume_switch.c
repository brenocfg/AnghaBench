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
struct tb_switch {int /*<<< orphan*/  dev; int /*<<< orphan*/  rpm_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icm_runtime_resume_switch(struct tb_switch *sw)
{
	if (tb_route(sw)) {
		if (!wait_for_completion_timeout(&sw->rpm_complete,
						 msecs_to_jiffies(500))) {
			dev_dbg(&sw->dev, "runtime resuming timed out\n");
		}
	}
	return 0;
}