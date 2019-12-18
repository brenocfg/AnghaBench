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
struct TYPE_4__ {scalar_t__ id; } ;
struct uclogic_params {TYPE_1__ pen; } ;
struct uclogic_drvdata {TYPE_3__* pen_input; struct uclogic_params params; } ;
struct hid_input {TYPE_3__* input; TYPE_2__* report; } ;
struct hid_field {int application; } ;
struct hid_device {char const* name; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ id; struct hid_field** field; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HID_CP_CONSUMER_CONTROL 133 
#define  HID_DG_PEN 132 
#define  HID_GD_KEYBOARD 131 
#define  HID_GD_KEYPAD 130 
#define  HID_GD_MOUSE 129 
#define  HID_GD_SYSTEM_CONTROL 128 
 char* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 struct uclogic_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int uclogic_input_configured(struct hid_device *hdev,
		struct hid_input *hi)
{
	struct uclogic_drvdata *drvdata = hid_get_drvdata(hdev);
	struct uclogic_params *params = &drvdata->params;
	char *name;
	const char *suffix = NULL;
	struct hid_field *field;
	size_t len;

	/* no report associated (HID_QUIRK_MULTI_INPUT not set) */
	if (!hi->report)
		return 0;

	/*
	 * If this is the input corresponding to the pen report
	 * in need of tweaking.
	 */
	if (hi->report->id == params->pen.id) {
		/* Remember the input device so we can simulate events */
		drvdata->pen_input = hi->input;
	}

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