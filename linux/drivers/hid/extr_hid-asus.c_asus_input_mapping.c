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
struct hid_field {int application; } ;
struct hid_device {int dummy; } ;
struct asus_drvdata {int quirks; int enable_backlight; } ;
struct TYPE_2__ {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_3 ; 
 int /*<<< orphan*/  BTN_4 ; 
 int /*<<< orphan*/  BTN_5 ; 
 int /*<<< orphan*/  BTN_6 ; 
 int /*<<< orphan*/  BTN_7 ; 
 int /*<<< orphan*/  BTN_8 ; 
 int /*<<< orphan*/  BTN_9 ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  EV_REP ; 
 int HID_GD_MOUSE ; 
 int HID_UP_BUTTON ; 
 int HID_UP_CONSUMER ; 
 int HID_UP_GENDESK ; 
 int HID_UP_GENDEVCTRLS ; 
 int HID_UP_MSVENDOR ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_BRIGHTNESSDOWN ; 
 int /*<<< orphan*/  KEY_BRIGHTNESSUP ; 
 int /*<<< orphan*/  KEY_CALC ; 
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  KEY_DISPLAY_OFF ; 
 int /*<<< orphan*/  KEY_F21 ; 
 int /*<<< orphan*/  KEY_KBDILLUMDOWN ; 
 int /*<<< orphan*/  KEY_KBDILLUMUP ; 
 int /*<<< orphan*/  KEY_MICMUTE ; 
 int /*<<< orphan*/  KEY_PROG1 ; 
 int /*<<< orphan*/  KEY_PROG2 ; 
 int /*<<< orphan*/  KEY_PROG3 ; 
 int /*<<< orphan*/  KEY_PROG4 ; 
 int /*<<< orphan*/  KEY_RFKILL ; 
 int /*<<< orphan*/  KEY_SLEEP ; 
 int /*<<< orphan*/  KEY_WLAN ; 
 int QUIRK_NO_CONSUMER_USAGES ; 
 int QUIRK_SKIP_INPUT_MAPPING ; 
 int QUIRK_T100CHI ; 
 int QUIRK_T90CHI ; 
 int QUIRK_USE_KBD_BACKLIGHT ; 
 int /*<<< orphan*/  asus_map_key_clear (int /*<<< orphan*/ ) ; 
 struct asus_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit,
		int *max)
{
	struct asus_drvdata *drvdata = hid_get_drvdata(hdev);

	if (drvdata->quirks & QUIRK_SKIP_INPUT_MAPPING) {
		/* Don't map anything from the HID report.
		 * We do it all manually in asus_input_configured
		 */
		return -1;
	}

	/*
	 * Ignore a bunch of bogus collections in the T100CHI descriptor.
	 * This avoids a bunch of non-functional hid_input devices getting
	 * created because of the T100CHI using HID_QUIRK_MULTI_INPUT.
	 */
	if (drvdata->quirks & (QUIRK_T100CHI | QUIRK_T90CHI)) {
		if (field->application == (HID_UP_GENDESK | 0x0080) ||
		    usage->hid == (HID_UP_GENDEVCTRLS | 0x0024) ||
		    usage->hid == (HID_UP_GENDEVCTRLS | 0x0025) ||
		    usage->hid == (HID_UP_GENDEVCTRLS | 0x0026))
			return -1;
		/*
		 * We use the hid_input for the mouse report for the touchpad,
		 * keep the left button, to avoid the core removing it.
		 */
		if (field->application == HID_GD_MOUSE &&
		    usage->hid != (HID_UP_BUTTON | 1))
			return -1;
	}

	/* ASUS-specific keyboard hotkeys */
	if ((usage->hid & HID_USAGE_PAGE) == 0xff310000) {
		set_bit(EV_REP, hi->input->evbit);
		switch (usage->hid & HID_USAGE) {
		case 0x10: asus_map_key_clear(KEY_BRIGHTNESSDOWN);	break;
		case 0x20: asus_map_key_clear(KEY_BRIGHTNESSUP);		break;
		case 0x35: asus_map_key_clear(KEY_DISPLAY_OFF);		break;
		case 0x6c: asus_map_key_clear(KEY_SLEEP);		break;
		case 0x7c: asus_map_key_clear(KEY_MICMUTE);		break;
		case 0x82: asus_map_key_clear(KEY_CAMERA);		break;
		case 0x88: asus_map_key_clear(KEY_RFKILL);			break;
		case 0xb5: asus_map_key_clear(KEY_CALC);			break;
		case 0xc4: asus_map_key_clear(KEY_KBDILLUMUP);		break;
		case 0xc5: asus_map_key_clear(KEY_KBDILLUMDOWN);		break;

		/* ASUS touchpad toggle */
		case 0x6b: asus_map_key_clear(KEY_F21);			break;

		/* ROG key */
		case 0x38: asus_map_key_clear(KEY_PROG1);		break;

		/* Fn+C ASUS Splendid */
		case 0xba: asus_map_key_clear(KEY_PROG2);		break;

		/* Fn+Space Power4Gear Hybrid */
		case 0x5c: asus_map_key_clear(KEY_PROG3);		break;

		/* Fn+F5 "fan" symbol on FX503VD */
		case 0x99: asus_map_key_clear(KEY_PROG4);		break;

		default:
			/* ASUS lazily declares 256 usages, ignore the rest,
			 * as some make the keyboard appear as a pointer device. */
			return -1;
		}

		/*
		 * Check and enable backlight only on devices with UsagePage ==
		 * 0xff31 to avoid initializing the keyboard firmware multiple
		 * times on devices with multiple HID descriptors but same
		 * PID/VID.
		 */
		if (drvdata->quirks & QUIRK_USE_KBD_BACKLIGHT)
			drvdata->enable_backlight = true;

		return 1;
	}

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOR) {
		set_bit(EV_REP, hi->input->evbit);
		switch (usage->hid & HID_USAGE) {
		case 0xff01: asus_map_key_clear(BTN_1);	break;
		case 0xff02: asus_map_key_clear(BTN_2);	break;
		case 0xff03: asus_map_key_clear(BTN_3);	break;
		case 0xff04: asus_map_key_clear(BTN_4);	break;
		case 0xff05: asus_map_key_clear(BTN_5);	break;
		case 0xff06: asus_map_key_clear(BTN_6);	break;
		case 0xff07: asus_map_key_clear(BTN_7);	break;
		case 0xff08: asus_map_key_clear(BTN_8);	break;
		case 0xff09: asus_map_key_clear(BTN_9);	break;
		case 0xff0a: asus_map_key_clear(BTN_A);	break;
		case 0xff0b: asus_map_key_clear(BTN_B);	break;
		case 0x00f1: asus_map_key_clear(KEY_WLAN);	break;
		case 0x00f2: asus_map_key_clear(KEY_BRIGHTNESSDOWN);	break;
		case 0x00f3: asus_map_key_clear(KEY_BRIGHTNESSUP);	break;
		case 0x00f4: asus_map_key_clear(KEY_DISPLAY_OFF);	break;
		case 0x00f7: asus_map_key_clear(KEY_CAMERA);	break;
		case 0x00f8: asus_map_key_clear(KEY_PROG1);	break;
		default:
			return 0;
		}

		return 1;
	}

	if (drvdata->quirks & QUIRK_NO_CONSUMER_USAGES &&
		(usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER) {
		switch (usage->hid & HID_USAGE) {
		case 0xe2: /* Mute */
		case 0xe9: /* Volume up */
		case 0xea: /* Volume down */
			return 0;
		default:
			/* Ignore dummy Consumer usages which make the
			 * keyboard incorrectly appear as a pointer device.
			 */
			return -1;
		}
	}

	return 0;
}