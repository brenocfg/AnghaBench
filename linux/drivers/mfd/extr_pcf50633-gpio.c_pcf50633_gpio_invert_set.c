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
struct pcf50633 {int dummy; } ;

/* Variables and functions */
 int PCF50633_GPIO1 ; 
 int PCF50633_REG_GPIO1CFG ; 
 int pcf50633_reg_set_bit_mask (struct pcf50633*,int,int,int) ; 

int pcf50633_gpio_invert_set(struct pcf50633 *pcf, int gpio, int invert)
{
	u8 val, reg;

	reg = gpio - PCF50633_GPIO1 + PCF50633_REG_GPIO1CFG;
	val = !!invert << 3;

	return pcf50633_reg_set_bit_mask(pcf, reg, 1 << 3, val);
}