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
 int /*<<< orphan*/  vexpress_power_off_device ; 
 int /*<<< orphan*/  vexpress_reset_do (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void vexpress_power_off(void)
{
	vexpress_reset_do(vexpress_power_off_device, "power off");
}