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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int MAX77802_REG_PWRON ; 
 unsigned int MAX77802_REG_STATUS1 ; 
 unsigned int MAX77802_REG_STATUS2 ; 
 scalar_t__ max77802_is_precious_reg (struct device*,unsigned int) ; 

__attribute__((used)) static bool max77802_pmic_is_volatile_reg(struct device *dev, unsigned int reg)
{
	return (max77802_is_precious_reg(dev, reg) ||
		reg == MAX77802_REG_STATUS1 || reg == MAX77802_REG_STATUS2 ||
		reg == MAX77802_REG_PWRON);
}