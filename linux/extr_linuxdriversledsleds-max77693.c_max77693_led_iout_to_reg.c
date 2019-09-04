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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ FLASH_IOUT_MIN ; 
 scalar_t__ FLASH_IOUT_STEP ; 

__attribute__((used)) static u8 max77693_led_iout_to_reg(u32 ua)
{
	if (ua < FLASH_IOUT_MIN)
		ua = FLASH_IOUT_MIN;
	return (ua - FLASH_IOUT_MIN) / FLASH_IOUT_STEP;
}