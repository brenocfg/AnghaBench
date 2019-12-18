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
struct s5m8767_info {int buck_gpioindex; int /*<<< orphan*/ * buck_gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int s5m8767_set_low(struct s5m8767_info *s5m8767)
{
	int temp_index = s5m8767->buck_gpioindex;

	gpio_set_value(s5m8767->buck_gpios[2], temp_index & 0x1);
	gpio_set_value(s5m8767->buck_gpios[1], (temp_index >> 1) & 0x1);
	gpio_set_value(s5m8767->buck_gpios[0], (temp_index >> 2) & 0x1);

	return 0;
}