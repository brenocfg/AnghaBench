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
 unsigned int REG_BANK ; 
 unsigned int REG_PWM (int) ; 

__attribute__((used)) static bool nct7802_regmap_is_volatile(struct device *dev, unsigned int reg)
{
	return (reg != REG_BANK && reg <= 0x20) ||
		(reg >= REG_PWM(0) && reg <= REG_PWM(2));
}