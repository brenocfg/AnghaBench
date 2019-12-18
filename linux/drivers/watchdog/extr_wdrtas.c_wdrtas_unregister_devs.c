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
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdrtas_miscdev ; 
 int /*<<< orphan*/  wdrtas_tempdev ; 
 scalar_t__ wdrtas_token_get_sensor_state ; 

__attribute__((used)) static void wdrtas_unregister_devs(void)
{
	misc_deregister(&wdrtas_miscdev);
	if (wdrtas_token_get_sensor_state != RTAS_UNKNOWN_SERVICE)
		misc_deregister(&wdrtas_tempdev);
}