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
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_3__ dev; } ;
struct TYPE_4__ {unsigned short bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int HID_UP_CONSUMER ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_BACK ; 
 int /*<<< orphan*/  KEY_CALC ; 
 int /*<<< orphan*/  KEY_COMPUTER ; 
 int /*<<< orphan*/  KEY_EMAIL ; 
 int /*<<< orphan*/  KEY_FAVORITES ; 
 int /*<<< orphan*/  KEY_FORWARD ; 
 int /*<<< orphan*/  KEY_MEDIA ; 
 int /*<<< orphan*/  KEY_REFRESH ; 
 int /*<<< orphan*/  KEY_SEARCH ; 
 int /*<<< orphan*/  KEY_STOP ; 
 int /*<<< orphan*/  KEY_WWW ; 
 int /*<<< orphan*/  dbg_hid (char*,int) ; 
 int /*<<< orphan*/  samsung_kbd_mouse_map_key_clear (int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int samsung_kbd_mouse_input_mapping(struct hid_device *hdev,
	struct hid_input *hi, struct hid_field *field, struct hid_usage *usage,
	unsigned long **bit, int *max)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	unsigned short ifnum = intf->cur_altsetting->desc.bInterfaceNumber;

	if (1 != ifnum || HID_UP_CONSUMER != (usage->hid & HID_USAGE_PAGE))
		return 0;

	dbg_hid("samsung wireless keyboard/mouse input mapping event [0x%x]\n",
		usage->hid & HID_USAGE);

	switch (usage->hid & HID_USAGE) {
	/* report 2 */
	case 0x183: samsung_kbd_mouse_map_key_clear(KEY_MEDIA); break;
	case 0x195: samsung_kbd_mouse_map_key_clear(KEY_EMAIL);	break;
	case 0x196: samsung_kbd_mouse_map_key_clear(KEY_CALC); break;
	case 0x197: samsung_kbd_mouse_map_key_clear(KEY_COMPUTER); break;
	case 0x22b: samsung_kbd_mouse_map_key_clear(KEY_SEARCH); break;
	case 0x22c: samsung_kbd_mouse_map_key_clear(KEY_WWW); break;
	case 0x22d: samsung_kbd_mouse_map_key_clear(KEY_BACK); break;
	case 0x22e: samsung_kbd_mouse_map_key_clear(KEY_FORWARD); break;
	case 0x22f: samsung_kbd_mouse_map_key_clear(KEY_FAVORITES); break;
	case 0x230: samsung_kbd_mouse_map_key_clear(KEY_REFRESH); break;
	case 0x231: samsung_kbd_mouse_map_key_clear(KEY_STOP); break;
	default:
		return 0;
	}

	return 1;
}