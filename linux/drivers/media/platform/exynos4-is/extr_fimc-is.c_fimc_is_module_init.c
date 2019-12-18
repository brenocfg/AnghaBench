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
 int /*<<< orphan*/  fimc_is_driver ; 
 int fimc_is_register_i2c_driver () ; 
 int /*<<< orphan*/  fimc_is_unregister_i2c_driver () ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fimc_is_module_init(void)
{
	int ret;

	ret = fimc_is_register_i2c_driver();
	if (ret < 0)
		return ret;

	ret = platform_driver_register(&fimc_is_driver);

	if (ret < 0)
		fimc_is_unregister_i2c_driver();

	return ret;
}