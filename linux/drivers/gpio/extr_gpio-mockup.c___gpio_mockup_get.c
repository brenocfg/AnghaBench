#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_mockup_chip {TYPE_1__* lines; } ;
struct TYPE_2__ {int value; } ;

/* Variables and functions */

__attribute__((used)) static int __gpio_mockup_get(struct gpio_mockup_chip *chip,
			     unsigned int offset)
{
	return chip->lines[offset].value;
}