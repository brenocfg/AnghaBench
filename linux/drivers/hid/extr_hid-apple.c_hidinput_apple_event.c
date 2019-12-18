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
typedef  scalar_t__ u16 ;
struct input_dev {int /*<<< orphan*/  led; int /*<<< orphan*/  key; } ;
struct hid_usage {int /*<<< orphan*/  type; scalar_t__ code; } ;
struct hid_device {int product; scalar_t__ country; } ;
struct apple_sc {int fn_on; int quirks; int /*<<< orphan*/  pressed_numlock; } ;
struct apple_key_translation {int flags; scalar_t__ to; scalar_t__ from; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int APPLE_FLAG_FKEY ; 
 int APPLE_NUMLOCK_EMULATION ; 
 scalar_t__ HID_COUNTRY_INTERNATIONAL_ISO ; 
 scalar_t__ KEY_FN ; 
 scalar_t__ LED_NUML ; 
 int USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS ; 
 int USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI ; 
 struct apple_key_translation* apple_find_translation (struct apple_key_translation const*,scalar_t__) ; 
 struct apple_key_translation* apple_fn_keys ; 
 struct apple_key_translation const* apple_iso_keyboard ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int fnmode ; 
 struct apple_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ iso_layout ; 
 struct apple_key_translation* macbookair_fn_keys ; 
 struct apple_key_translation* powerbook_fn_keys ; 
 struct apple_key_translation const* powerbook_numlock_keys ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ swap_opt_cmd ; 
 struct apple_key_translation const* swapped_option_cmd_keys ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidinput_apple_event(struct hid_device *hid, struct input_dev *input,
		struct hid_usage *usage, __s32 value)
{
	struct apple_sc *asc = hid_get_drvdata(hid);
	const struct apple_key_translation *trans, *table;
	bool do_translate;
	u16 code = 0;

	if (usage->code == KEY_FN) {
		asc->fn_on = !!value;
		input_event(input, usage->type, usage->code, value);
		return 1;
	}

	if (fnmode) {
		if (hid->product >= USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI &&
				hid->product <= USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS)
			table = macbookair_fn_keys;
		else if (hid->product < 0x21d || hid->product >= 0x300)
			table = powerbook_fn_keys;
		else
			table = apple_fn_keys;

		trans = apple_find_translation (table, usage->code);

		if (trans) {
			if (test_bit(trans->from, input->key))
				code = trans->from;
			else if (test_bit(trans->to, input->key))
				code = trans->to;

			if (!code) {
				if (trans->flags & APPLE_FLAG_FKEY) {
					switch (fnmode) {
					case 1:
						do_translate = !asc->fn_on;
						break;
					case 2:
						do_translate = asc->fn_on;
						break;
					default:
						/* should never happen */
						do_translate = false;
					}
				} else {
					do_translate = asc->fn_on;
				}

				code = do_translate ? trans->to : trans->from;
			}

			input_event(input, usage->type, code, value);
			return 1;
		}

		if (asc->quirks & APPLE_NUMLOCK_EMULATION &&
				(test_bit(usage->code, asc->pressed_numlock) ||
				test_bit(LED_NUML, input->led))) {
			trans = apple_find_translation(powerbook_numlock_keys,
					usage->code);

			if (trans) {
				if (value)
					set_bit(usage->code,
							asc->pressed_numlock);
				else
					clear_bit(usage->code,
							asc->pressed_numlock);

				input_event(input, usage->type, trans->to,
						value);
			}

			return 1;
		}
	}

	if (iso_layout) {
		if (hid->country == HID_COUNTRY_INTERNATIONAL_ISO) {
			trans = apple_find_translation(apple_iso_keyboard, usage->code);
			if (trans) {
				input_event(input, usage->type, trans->to, value);
				return 1;
			}
		}
	}

	if (swap_opt_cmd) {
		trans = apple_find_translation(swapped_option_cmd_keys, usage->code);
		if (trans) {
			input_event(input, usage->type, trans->to, value);
			return 1;
		}
	}

	return 0;
}