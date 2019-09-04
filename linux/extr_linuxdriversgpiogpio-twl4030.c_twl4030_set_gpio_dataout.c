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

/* Variables and functions */
 int BIT (int) ; 
 int REG_CLEARGPIODATAOUT1 ; 
 int REG_SETGPIODATAOUT1 ; 
 int gpio_twl4030_write (int,int) ; 

__attribute__((used)) static int twl4030_set_gpio_dataout(int gpio, int enable)
{
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 base = 0;

	if (enable)
		base = REG_SETGPIODATAOUT1 + d_bnk;
	else
		base = REG_CLEARGPIODATAOUT1 + d_bnk;

	return gpio_twl4030_write(base, d_msk);
}