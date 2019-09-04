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
struct hid_input {TYPE_2__* input; TYPE_1__* report; } ;
struct hid_field {int application; } ;
struct hid_device {char const* name; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct hid_field** field; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HID_CP_CONSUMER_CONTROL 133 
#define  HID_DG_PEN 132 
#define  HID_GD_KEYBOARD 131 
#define  HID_GD_KEYPAD 130 
#define  HID_GD_MOUSE 129 
#define  HID_GD_SYSTEM_CONTROL 128 
 char* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int uclogic_input_configured(struct hid_device *hdev,
		struct hid_input *hi)
{
	char *name;
	const char *suffix = NULL;
	struct hid_field *field;
	size_t len;

	/* no report associated (HID_QUIRK_MULTI_INPUT not set) */
	if (!hi->report)
		return 0;

	field = hi->report->field[0];

	switch (field->application) {
	case HID_GD_KEYBOARD:
		suffix = "Keyboard";
		break;
	case HID_GD_MOUSE:
		suffix = "Mouse";
		break;
	case HID_GD_KEYPAD:
		suffix = "Pad";
		break;
	case HID_DG_PEN:
		suffix = "Pen";
		break;
	case HID_CP_CONSUMER_CONTROL:
		suffix = "Consumer Control";
		break;
	case HID_GD_SYSTEM_CONTROL:
		suffix = "System Control";
		break;
	}

	if (suffix) {
		len = strlen(hdev->name) + 2 + strlen(suffix);
		name = devm_kzalloc(&hi->input->dev, len, GFP_KERNEL);
		if (name) {
			snprintf(name, len, "%s %s", hdev->name, suffix);
			hi->input->name = name;
		}
	}

	return 0;
}