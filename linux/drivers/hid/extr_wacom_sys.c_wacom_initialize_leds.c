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
struct TYPE_6__ {int llv; int max_llv; int hlv; int max_hlv; int img_lum; } ;
struct TYPE_4__ {int device_type; int type; } ;
struct TYPE_5__ {TYPE_1__ features; } ;
struct wacom {int /*<<< orphan*/  hdev; TYPE_3__ led; int /*<<< orphan*/  generic_has_leds; TYPE_2__ wacom_wac; } ;

/* Variables and functions */
#define  HID_GENERIC 142 
#define  INTUOS4 141 
#define  INTUOS4L 140 
#define  INTUOS4S 139 
#define  INTUOS4WL 138 
#define  INTUOS5 137 
#define  INTUOS5L 136 
#define  INTUOS5S 135 
#define  INTUOSP2_BT 134 
#define  INTUOSPL 133 
#define  INTUOSPM 132 
#define  INTUOSPS 131 
#define  REMOTE 130 
#define  WACOM_21UX2 129 
#define  WACOM_24HD 128 
 int WACOM_DEVICETYPE_PAD ; 
 int /*<<< orphan*/  cintiq_led_attr_group ; 
 int /*<<< orphan*/  generic_led_attr_group ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  intuos4_led_attr_group ; 
 int /*<<< orphan*/  intuos5_led_attr_group ; 
 int wacom_devm_sysfs_create_group (struct wacom*,int /*<<< orphan*/ *) ; 
 int wacom_led_groups_allocate (struct wacom*,int) ; 
 int wacom_leds_alloc_and_register (struct wacom*,int,int,int) ; 

int wacom_initialize_leds(struct wacom *wacom)
{
	int error;

	if (!(wacom->wacom_wac.features.device_type & WACOM_DEVICETYPE_PAD))
		return 0;

	/* Initialize default values */
	switch (wacom->wacom_wac.features.type) {
	case HID_GENERIC:
		if (!wacom->generic_has_leds)
			return 0;
		wacom->led.llv = 100;
		wacom->led.max_llv = 100;

		error = wacom_leds_alloc_and_register(wacom, 1, 4, false);
		if (error) {
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			return error;
		}

		error = wacom_devm_sysfs_create_group(wacom,
						      &generic_led_attr_group);
		break;

	case INTUOS4S:
	case INTUOS4:
	case INTUOS4WL:
	case INTUOS4L:
		wacom->led.llv = 10;
		wacom->led.hlv = 20;
		wacom->led.max_llv = 127;
		wacom->led.max_hlv = 127;
		wacom->led.img_lum = 10;

		error = wacom_leds_alloc_and_register(wacom, 1, 4, false);
		if (error) {
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			return error;
		}

		error = wacom_devm_sysfs_create_group(wacom,
						      &intuos4_led_attr_group);
		break;

	case WACOM_24HD:
	case WACOM_21UX2:
		wacom->led.llv = 0;
		wacom->led.hlv = 0;
		wacom->led.img_lum = 0;

		error = wacom_leds_alloc_and_register(wacom, 2, 4, false);
		if (error) {
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			return error;
		}

		error = wacom_devm_sysfs_create_group(wacom,
						      &cintiq_led_attr_group);
		break;

	case INTUOS5S:
	case INTUOS5:
	case INTUOS5L:
	case INTUOSPS:
	case INTUOSPM:
	case INTUOSPL:
		wacom->led.llv = 32;
		wacom->led.max_llv = 96;

		error = wacom_leds_alloc_and_register(wacom, 1, 4, false);
		if (error) {
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			return error;
		}

		error = wacom_devm_sysfs_create_group(wacom,
						      &intuos5_led_attr_group);
		break;

	case INTUOSP2_BT:
		wacom->led.llv = 50;
		wacom->led.max_llv = 100;
		error = wacom_leds_alloc_and_register(wacom, 1, 4, false);
		if (error) {
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			return error;
		}
		return 0;

	case REMOTE:
		wacom->led.llv = 255;
		wacom->led.max_llv = 255;
		error = wacom_led_groups_allocate(wacom, 5);
		if (error) {
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			return error;
		}
		return 0;

	default:
		return 0;
	}

	if (error) {
		hid_err(wacom->hdev,
			"cannot create sysfs group err: %d\n", error);
		return error;
	}

	return 0;
}