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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static int get_gpio_pin_params(u32 pin_num, u32 *p_translatedpin_num,
		u32 *p_group_num, u32 *p_group_cfg) {

	*p_group_cfg = 1;

	if (pin_num <= 1)	{
		*p_translatedpin_num = 0;
		*p_group_num = 9;
		*p_group_cfg = 2;
	} else if (pin_num >= 2 && pin_num <= 6) {
		*p_translatedpin_num = 2;
		*p_group_num = 0;
		*p_group_cfg = 2;
	} else if (pin_num >= 7 && pin_num <= 11) {
		*p_translatedpin_num = 7;
		*p_group_num = 1;
	} else if (pin_num >= 12 && pin_num <= 15) {
		*p_translatedpin_num = 12;
		*p_group_num = 2;
		*p_group_cfg = 3;
	} else if (pin_num == 16) {
		*p_translatedpin_num = 16;
		*p_group_num = 23;
	} else if (pin_num >= 17 && pin_num <= 24) {
		*p_translatedpin_num = 17;
		*p_group_num = 3;
	} else if (pin_num == 25) {
		*p_translatedpin_num = 25;
		*p_group_num = 6;
	} else if (pin_num >= 26 && pin_num <= 28) {
		*p_translatedpin_num = 26;
		*p_group_num = 4;
	} else if (pin_num == 29) {
		*p_translatedpin_num = 29;
		*p_group_num = 5;
		*p_group_cfg = 2;
	} else if (pin_num == 30) {
		*p_translatedpin_num = 30;
		*p_group_num = 8;
	} else if (pin_num == 31) {
		*p_translatedpin_num = 31;
		*p_group_num = 17;
	} else
		return -1;

	*p_group_cfg <<= 24;

	return 0;
}