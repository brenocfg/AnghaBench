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
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int htcpld_direction_input(struct gpio_chip *chip,
					unsigned offset)
{
	/*
	 * No-op: this function can only be called on the input chip.
	 * We do however make sure the offset is within range.
	 */
	return (offset < chip->ngpio) ? 0 : -EINVAL;
}