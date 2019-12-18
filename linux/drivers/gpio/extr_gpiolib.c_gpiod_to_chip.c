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
struct gpio_desc {TYPE_1__* gdev; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {struct gpio_chip* chip; } ;

/* Variables and functions */

struct gpio_chip *gpiod_to_chip(const struct gpio_desc *desc)
{
	if (!desc || !desc->gdev)
		return NULL;
	return desc->gdev->chip;
}