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
struct vga_switcheroo_client {int pwr_state; TYPE_1__* pdev; scalar_t__ driver_power_control; } ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int VGA_SWITCHEROO_OFF ; 
 int VGA_SWITCHEROO_ON ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_enabled (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum vga_switcheroo_state
vga_switcheroo_pwr_state(struct vga_switcheroo_client *client)
{
	if (client->driver_power_control)
		if (pm_runtime_enabled(&client->pdev->dev) &&
		    pm_runtime_active(&client->pdev->dev))
			return VGA_SWITCHEROO_ON;
		else
			return VGA_SWITCHEROO_OFF;
	else
		return client->pwr_state;
}