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
struct TYPE_5__ {int device_type; int /*<<< orphan*/  type; } ;
struct wacom_wac {TYPE_1__* shared; scalar_t__ has_mute_touch_switch; TYPE_3__* touch_input; TYPE_2__ features; } ;
struct TYPE_6__ {int /*<<< orphan*/  evbit; } ;
struct TYPE_4__ {int has_mute_touch_switch; int is_touch_on; TYPE_3__* touch_input; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  SW_MUTE_DEVICE ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int /*<<< orphan*/  input_set_capability (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_set_shared_values(struct wacom_wac *wacom_wac)
{
	if (wacom_wac->features.device_type & WACOM_DEVICETYPE_TOUCH) {
		wacom_wac->shared->type = wacom_wac->features.type;
		wacom_wac->shared->touch_input = wacom_wac->touch_input;
	}

	if (wacom_wac->has_mute_touch_switch) {
		wacom_wac->shared->has_mute_touch_switch = true;
		wacom_wac->shared->is_touch_on = true;
	}

	if (wacom_wac->shared->has_mute_touch_switch &&
	    wacom_wac->shared->touch_input) {
		set_bit(EV_SW, wacom_wac->shared->touch_input->evbit);
		input_set_capability(wacom_wac->shared->touch_input, EV_SW,
				     SW_MUTE_DEVICE);
	}
}