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
struct hid_usage {int hid; } ;
struct hid_input {TYPE_1__* input; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int HID_UP_CUSTOM ; 
 int HID_UP_MSVENDOR ; 
 int /*<<< orphan*/  KEY_FN ; 
 int /*<<< orphan*/  apple_setup_input (TYPE_1__*) ; 
 int /*<<< orphan*/  hid_map_usage_clear (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apple_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if (usage->hid == (HID_UP_CUSTOM | 0x0003) ||
			usage->hid == (HID_UP_MSVENDOR | 0x0003)) {
		/* The fn key on Apple USB keyboards */
		set_bit(EV_REP, hi->input->evbit);
		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, KEY_FN);
		apple_setup_input(hi->input);
		return 1;
	}

	/* we want the hid layer to go through standard path (set and ignore) */
	return 0;
}