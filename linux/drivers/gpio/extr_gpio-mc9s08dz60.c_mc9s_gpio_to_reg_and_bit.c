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
 int GPIO_NUM_PER_GROUP ; 

__attribute__((used)) static void mc9s_gpio_to_reg_and_bit(int offset, u8 *reg, u8 *bit)
{
	*reg = 0x20 + offset / GPIO_NUM_PER_GROUP;
	*bit = offset % GPIO_NUM_PER_GROUP;
}