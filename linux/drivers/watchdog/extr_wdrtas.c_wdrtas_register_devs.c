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
 scalar_t__ RTAS_UNKNOWN_SERVICE ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  wdrtas_miscdev ; 
 int /*<<< orphan*/  wdrtas_tempdev ; 
 scalar_t__ wdrtas_token_get_sensor_state ; 

__attribute__((used)) static int wdrtas_register_devs(void)
{
	int result;

	result = misc_register(&wdrtas_miscdev);
	if (result) {
		pr_err("couldn't register watchdog misc device. Terminating watchdog code.\n");
		return result;
	}

	if (wdrtas_token_get_sensor_state != RTAS_UNKNOWN_SERVICE) {
		result = misc_register(&wdrtas_tempdev);
		if (result) {
			pr_warn("couldn't register watchdog temperature misc device. Continuing without temperature support.\n");
			wdrtas_token_get_sensor_state = RTAS_UNKNOWN_SERVICE;
		}
	}

	return 0;
}