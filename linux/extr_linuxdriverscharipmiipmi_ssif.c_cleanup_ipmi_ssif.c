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
 int /*<<< orphan*/  free_ssif_clients () ; 
 int /*<<< orphan*/  i2c_del_driver (int /*<<< orphan*/ *) ; 
 int initialized ; 
 int /*<<< orphan*/  ipmi_driver ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssif_i2c_driver ; 

__attribute__((used)) static void cleanup_ipmi_ssif(void)
{
	if (!initialized)
		return;

	initialized = false;

	i2c_del_driver(&ssif_i2c_driver);

	platform_driver_unregister(&ipmi_driver);

	free_ssif_clients();
}