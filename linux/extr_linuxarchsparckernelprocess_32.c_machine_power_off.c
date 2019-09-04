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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_POWER_OFF ; 
 scalar_t__ auxio_power_register ; 
 int /*<<< orphan*/  machine_halt () ; 
 TYPE_1__* of_console_device ; 
 int /*<<< orphan*/  sbus_readb (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ scons_pwroff ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void machine_power_off(void)
{
	if (auxio_power_register &&
	    (strcmp(of_console_device->type, "serial") || scons_pwroff)) {
		u8 power_register = sbus_readb(auxio_power_register);
		power_register |= AUXIO_POWER_OFF;
		sbus_writeb(power_register, auxio_power_register);
	}

	machine_halt();
}