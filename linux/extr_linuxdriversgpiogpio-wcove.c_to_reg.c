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
typedef  enum ctrl_register { ____Placeholder_ctrl_register } ctrl_register ;

/* Variables and functions */
 int CTRL_IN ; 
 unsigned int EOPNOTSUPP ; 
 int GPIO_IN_CTRL_BASE ; 
 int GPIO_OUT_CTRL_BASE ; 
 int WCOVE_GPIO_NUM ; 

__attribute__((used)) static inline unsigned int to_reg(int gpio, enum ctrl_register reg_type)
{
	unsigned int reg;

	if (gpio >= WCOVE_GPIO_NUM)
		return -EOPNOTSUPP;

	if (reg_type == CTRL_IN)
		reg = GPIO_IN_CTRL_BASE + gpio;
	else
		reg = GPIO_OUT_CTRL_BASE + gpio;

	return reg;
}