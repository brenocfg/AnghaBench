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
 scalar_t__ PNX833X_RESET_CONTROL ; 
 scalar_t__ PNX833X_RESET_CONTROL_2 ; 

void pnx833x_machine_restart(char *command)
{
	PNX833X_RESET_CONTROL_2 = 0;
	PNX833X_RESET_CONTROL = 0;
}