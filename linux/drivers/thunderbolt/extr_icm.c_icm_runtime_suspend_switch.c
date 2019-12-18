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
struct tb_switch {int /*<<< orphan*/  rpm_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 

__attribute__((used)) static int icm_runtime_suspend_switch(struct tb_switch *sw)
{
	if (tb_route(sw))
		reinit_completion(&sw->rpm_complete);
	return 0;
}