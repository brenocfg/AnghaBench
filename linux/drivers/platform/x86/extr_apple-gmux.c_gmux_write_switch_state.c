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
struct apple_gmux_data {scalar_t__ switch_state_ddc; scalar_t__ switch_state_display; scalar_t__ switch_state_external; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMUX_PORT_SWITCH_DDC ; 
 int /*<<< orphan*/  GMUX_PORT_SWITCH_DISPLAY ; 
 int /*<<< orphan*/  GMUX_PORT_SWITCH_EXTERNAL ; 
 scalar_t__ VGA_SWITCHEROO_IGD ; 
 int /*<<< orphan*/  gmux_write8 (struct apple_gmux_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gmux_write_switch_state(struct apple_gmux_data *gmux_data)
{
	if (gmux_data->switch_state_ddc == VGA_SWITCHEROO_IGD)
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_DDC, 1);
	else
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_DDC, 2);

	if (gmux_data->switch_state_display == VGA_SWITCHEROO_IGD)
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_DISPLAY, 2);
	else
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_DISPLAY, 3);

	if (gmux_data->switch_state_external == VGA_SWITCHEROO_IGD)
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL, 2);
	else
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL, 3);
}