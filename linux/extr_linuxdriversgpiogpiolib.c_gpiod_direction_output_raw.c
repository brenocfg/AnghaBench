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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_DESC (struct gpio_desc*) ; 
 int gpiod_direction_output_raw_commit (struct gpio_desc*,int) ; 

int gpiod_direction_output_raw(struct gpio_desc *desc, int value)
{
	VALIDATE_DESC(desc);
	return gpiod_direction_output_raw_commit(desc, value);
}