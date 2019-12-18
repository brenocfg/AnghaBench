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
 int /*<<< orphan*/  fimc_is_i2c_driver ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 

void fimc_is_unregister_i2c_driver(void)
{
	platform_driver_unregister(&fimc_is_i2c_driver);
}