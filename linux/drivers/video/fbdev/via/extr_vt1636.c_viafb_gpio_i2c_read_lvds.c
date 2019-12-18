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
typedef  int /*<<< orphan*/  u8 ;
struct lvds_setting_information {int dummy; } ;
struct lvds_chip_information {int /*<<< orphan*/  lvds_chip_slave_addr; int /*<<< orphan*/  i2c_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  viafb_i2c_readbyte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u8 viafb_gpio_i2c_read_lvds(struct lvds_setting_information
	*plvds_setting_info, struct lvds_chip_information *plvds_chip_info,
	u8 index)
{
	u8 data;

	viafb_i2c_readbyte(plvds_chip_info->i2c_port,
			   plvds_chip_info->lvds_chip_slave_addr, index, &data);
	return data;
}