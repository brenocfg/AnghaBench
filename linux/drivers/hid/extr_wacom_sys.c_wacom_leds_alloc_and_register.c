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
struct TYPE_4__ {TYPE_1__* pad_input; } ;
struct wacom {TYPE_2__ wacom_wac; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int wacom_led_groups_alloc_and_register_one (struct device*,struct wacom*,int,int,int) ; 
 int wacom_led_groups_allocate (struct wacom*,int) ; 

__attribute__((used)) static int wacom_leds_alloc_and_register(struct wacom *wacom, int group_count,
					 int led_per_group, bool read_only)
{
	struct device *dev;
	int i, error;

	if (!wacom->wacom_wac.pad_input)
		return -EINVAL;

	dev = &wacom->wacom_wac.pad_input->dev;

	error = wacom_led_groups_allocate(wacom, group_count);
	if (error)
		return error;

	for (i = 0; i < group_count; i++) {
		error = wacom_led_groups_alloc_and_register_one(dev, wacom, i,
								led_per_group,
								read_only);
		if (error)
			return error;
	}

	return 0;
}