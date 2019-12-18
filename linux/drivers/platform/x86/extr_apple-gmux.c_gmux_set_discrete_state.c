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
struct apple_gmux_data {int power_state; scalar_t__ gpe; int /*<<< orphan*/  powerchange_done; } ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;

/* Variables and functions */
 int /*<<< orphan*/  GMUX_PORT_DISCRETE_POWER ; 
 int VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  gmux_write8 (struct apple_gmux_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmux_set_discrete_state(struct apple_gmux_data *gmux_data,
				   enum vga_switcheroo_state state)
{
	reinit_completion(&gmux_data->powerchange_done);

	if (state == VGA_SWITCHEROO_ON) {
		gmux_write8(gmux_data, GMUX_PORT_DISCRETE_POWER, 1);
		gmux_write8(gmux_data, GMUX_PORT_DISCRETE_POWER, 3);
		pr_debug("Discrete card powered up\n");
	} else {
		gmux_write8(gmux_data, GMUX_PORT_DISCRETE_POWER, 1);
		gmux_write8(gmux_data, GMUX_PORT_DISCRETE_POWER, 0);
		pr_debug("Discrete card powered down\n");
	}

	gmux_data->power_state = state;

	if (gmux_data->gpe >= 0 &&
	    !wait_for_completion_interruptible_timeout(&gmux_data->powerchange_done,
						       msecs_to_jiffies(200)))
		pr_warn("Timeout waiting for gmux switch to complete\n");

	return 0;
}