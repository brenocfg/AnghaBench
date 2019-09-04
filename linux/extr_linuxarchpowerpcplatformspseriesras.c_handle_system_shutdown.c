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
#define  EPOW_SHUTDOWN_AMBIENT_TEMPERATURE_TOO_HIGH 131 
#define  EPOW_SHUTDOWN_LOSS_OF_CRITICAL_FUNCTIONS 130 
#define  EPOW_SHUTDOWN_NORMAL 129 
#define  EPOW_SHUTDOWN_ON_UPS 128 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  pr_err (char*,char) ; 

__attribute__((used)) static void handle_system_shutdown(char event_modifier)
{
	switch (event_modifier) {
	case EPOW_SHUTDOWN_NORMAL:
		pr_emerg("Power off requested\n");
		orderly_poweroff(true);
		break;

	case EPOW_SHUTDOWN_ON_UPS:
		pr_emerg("Loss of system power detected. System is running on"
			 " UPS/battery. Check RTAS error log for details\n");
		orderly_poweroff(true);
		break;

	case EPOW_SHUTDOWN_LOSS_OF_CRITICAL_FUNCTIONS:
		pr_emerg("Loss of system critical functions detected. Check"
			 " RTAS error log for details\n");
		orderly_poweroff(true);
		break;

	case EPOW_SHUTDOWN_AMBIENT_TEMPERATURE_TOO_HIGH:
		pr_emerg("High ambient temperature detected. Check RTAS"
			 " error log for details\n");
		orderly_poweroff(true);
		break;

	default:
		pr_err("Unknown power/cooling shutdown event (modifier = %d)\n",
			event_modifier);
	}
}