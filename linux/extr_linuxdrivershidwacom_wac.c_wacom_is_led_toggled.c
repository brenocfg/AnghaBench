#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ features; } ;
struct wacom {TYPE_3__ led; TYPE_2__ wacom_wac; } ;

/* Variables and functions */
 scalar_t__ WACOM_21UX2 ; 

__attribute__((used)) static bool wacom_is_led_toggled(struct wacom *wacom, int button_count,
				 int mask, int group)
{
	int button_per_group;

	/*
	 * 21UX2 has LED group 1 to the left and LED group 0
	 * to the right. We need to reverse the group to match this
	 * historical behavior.
	 */
	if (wacom->wacom_wac.features.type == WACOM_21UX2)
		group = 1 - group;

	button_per_group = button_count/wacom->led.count;

	return mask & (1 << (group * button_per_group));
}