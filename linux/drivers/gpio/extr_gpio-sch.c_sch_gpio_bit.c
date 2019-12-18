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
struct sch_gpio {unsigned int resume_base; } ;

/* Variables and functions */

__attribute__((used)) static unsigned sch_gpio_bit(struct sch_gpio *sch, unsigned gpio)
{
	if (gpio >= sch->resume_base)
		gpio -= sch->resume_base;
	return gpio % 8;
}