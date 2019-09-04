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
 int /*<<< orphan*/  S3C2410_GPB (int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int* power_state ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static void
usb_simtec_powercontrol(int port, int to)
{
	pr_debug("usb_simtec_powercontrol(%d,%d)\n", port, to);

	power_state[port] = to;

	if (power_state[0] && power_state[1])
		gpio_set_value(S3C2410_GPB(4), 0);
	else
		gpio_set_value(S3C2410_GPB(4), 1);
}