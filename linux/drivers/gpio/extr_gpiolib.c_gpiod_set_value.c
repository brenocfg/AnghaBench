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
struct TYPE_3__ {int /*<<< orphan*/  can_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_DESC_VOID (struct gpio_desc*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_nocheck (struct gpio_desc*,int) ; 

void gpiod_set_value(struct gpio_desc *desc, int value)
{
	VALIDATE_DESC_VOID(desc);
	/* Should be using gpiod_set_value_cansleep() */
	WARN_ON(desc->gdev->chip->can_sleep);
	gpiod_set_value_nocheck(desc, value);
}