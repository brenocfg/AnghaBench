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
struct lvds_setting_information {scalar_t__ LCDDithering; scalar_t__ device_lcd_dualedge; } ;
struct lvds_chip_information {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * common_init_data ; 
 int /*<<< orphan*/  dithering_disable_data ; 
 int /*<<< orphan*/  dithering_enable_data ; 
 int /*<<< orphan*/  dual_channel_enable_data ; 
 int /*<<< orphan*/  single_channel_enable_data ; 
 int /*<<< orphan*/  viafb_gpio_i2c_write_mask_lvds (struct lvds_setting_information*,struct lvds_chip_information*,int /*<<< orphan*/ ) ; 

void viafb_init_lvds_vt1636(struct lvds_setting_information
	*plvds_setting_info, struct lvds_chip_information *plvds_chip_info)
{
	int reg_num, i;

	/* Common settings: */
	reg_num = ARRAY_SIZE(common_init_data);
	for (i = 0; i < reg_num; i++)
		viafb_gpio_i2c_write_mask_lvds(plvds_setting_info,
			plvds_chip_info, common_init_data[i]);

	/* Input Data Mode Select */
	if (plvds_setting_info->device_lcd_dualedge)
		viafb_gpio_i2c_write_mask_lvds(plvds_setting_info,
			plvds_chip_info, dual_channel_enable_data);
	else
		viafb_gpio_i2c_write_mask_lvds(plvds_setting_info,
			plvds_chip_info, single_channel_enable_data);

	if (plvds_setting_info->LCDDithering)
		viafb_gpio_i2c_write_mask_lvds(plvds_setting_info,
			plvds_chip_info, dithering_enable_data);
	else
		viafb_gpio_i2c_write_mask_lvds(plvds_setting_info,
			plvds_chip_info, dithering_disable_data);
}