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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acs5k_i2c_device ; 
 int /*<<< orphan*/  acs5k_i2c_devs ; 
 int /*<<< orphan*/  acs5k_i2c_gpiod_table ; 
 int /*<<< orphan*/  gpiod_add_lookup_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_register_board_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acs5k_i2c_init(void)
{
	/* The gpio interface */
	gpiod_add_lookup_table(&acs5k_i2c_gpiod_table);
	platform_device_register(&acs5k_i2c_device);
	/* I2C devices */
	i2c_register_board_info(0, acs5k_i2c_devs,
				ARRAY_SIZE(acs5k_i2c_devs));
}