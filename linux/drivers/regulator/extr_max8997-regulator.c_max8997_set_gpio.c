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
struct max8997_data {int buck125_gpioindex; int /*<<< orphan*/ * buck125_gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void max8997_set_gpio(struct max8997_data *max8997)
{
	int set3 = (max8997->buck125_gpioindex) & 0x1;
	int set2 = ((max8997->buck125_gpioindex) >> 1) & 0x1;
	int set1 = ((max8997->buck125_gpioindex) >> 2) & 0x1;

	gpio_set_value(max8997->buck125_gpios[0], set1);
	gpio_set_value(max8997->buck125_gpios[1], set2);
	gpio_set_value(max8997->buck125_gpios[2], set3);
}