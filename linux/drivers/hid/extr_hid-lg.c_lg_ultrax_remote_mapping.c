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
struct TYPE_2__ {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REP ; 
 int HID_UP_LOGIVENDOR ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_AGAIN ; 
 int /*<<< orphan*/  KEY_ANGLE ; 
 int /*<<< orphan*/  KEY_AUDIO ; 
 int /*<<< orphan*/  KEY_CLOSE ; 
 int /*<<< orphan*/  KEY_DVD ; 
 int /*<<< orphan*/  KEY_HOME ; 
 int /*<<< orphan*/  KEY_LANGUAGE ; 
 int /*<<< orphan*/  KEY_LAST ; 
 int /*<<< orphan*/  KEY_MEDIA ; 
 int /*<<< orphan*/  KEY_MENU ; 
 int /*<<< orphan*/  KEY_MP3 ; 
 int /*<<< orphan*/  KEY_RED ; 
 int /*<<< orphan*/  KEY_SHUFFLE ; 
 int /*<<< orphan*/  KEY_SUBTITLE ; 
 int /*<<< orphan*/  KEY_TEXT ; 
 int /*<<< orphan*/  KEY_TV ; 
 int /*<<< orphan*/  KEY_VIDEO ; 
 int /*<<< orphan*/  lg_map_key_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lg_ultrax_remote_mapping(struct hid_input *hi,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_LOGIVENDOR)
		return 0;

	set_bit(EV_REP, hi->input->evbit);
	switch (usage->hid & HID_USAGE) {
	/* Reported on Logitech Ultra X Media Remote */
	case 0x004: lg_map_key_clear(KEY_AGAIN);	break;
	case 0x00d: lg_map_key_clear(KEY_HOME);		break;
	case 0x024: lg_map_key_clear(KEY_SHUFFLE);	break;
	case 0x025: lg_map_key_clear(KEY_TV);		break;
	case 0x026: lg_map_key_clear(KEY_MENU);		break;
	case 0x031: lg_map_key_clear(KEY_AUDIO);	break;
	case 0x032: lg_map_key_clear(KEY_TEXT);		break;
	case 0x033: lg_map_key_clear(KEY_LAST);		break;
	case 0x047: lg_map_key_clear(KEY_MP3);		break;
	case 0x048: lg_map_key_clear(KEY_DVD);		break;
	case 0x049: lg_map_key_clear(KEY_MEDIA);	break;
	case 0x04a: lg_map_key_clear(KEY_VIDEO);	break;
	case 0x04b: lg_map_key_clear(KEY_ANGLE);	break;
	case 0x04c: lg_map_key_clear(KEY_LANGUAGE);	break;
	case 0x04d: lg_map_key_clear(KEY_SUBTITLE);	break;
	case 0x051: lg_map_key_clear(KEY_RED);		break;
	case 0x052: lg_map_key_clear(KEY_CLOSE);	break;

	default:
		return 0;
	}
	return 1;
}