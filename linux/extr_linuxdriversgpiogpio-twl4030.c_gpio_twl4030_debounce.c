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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GPIO_DEBEN1 ; 
 int /*<<< orphan*/  TWL4030_MODULE_GPIO ; 
 int twl_i2c_write (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpio_twl4030_debounce(u32 debounce, u8 mmc_cd)
{
	u8		message[3];

	/* 30 msec of debouncing is always used for MMC card detect,
	 * and is optional for everything else.
	 */
	message[0] = (debounce & 0xff) | (mmc_cd & 0x03);
	debounce >>= 8;
	message[1] = (debounce & 0xff);
	debounce >>= 8;
	message[2] = (debounce & 0x03);

	return twl_i2c_write(TWL4030_MODULE_GPIO, message,
				REG_GPIO_DEBEN1, 3);
}