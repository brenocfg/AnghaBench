#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_desc {TYPE_2__* gdev; } ;
struct TYPE_4__ {TYPE_1__* chip; } ;
struct TYPE_3__ {int can_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_DESC (struct gpio_desc const*) ; 

int gpiod_cansleep(const struct gpio_desc *desc)
{
	VALIDATE_DESC(desc);
	return desc->gdev->chip->can_sleep;
}