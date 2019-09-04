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
struct mt_class {scalar_t__ is_indirect; } ;
struct mt_device {int is_buttonpad; scalar_t__ maxcontacts; scalar_t__ serial_maybe; struct mt_class mtclass; } ;
struct mt_application {int mt_flags; int quirks; int buttons_count; int /*<<< orphan*/  pending_palm_slots; } ;
struct input_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  propbit; } ;
struct hid_input {struct input_dev* input; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (scalar_t__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 scalar_t__ MT_DEFAULT_MAXCONTACT ; 
 int MT_QUIRK_NOT_SEEN_MEANS_UP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mt_device* hid_get_drvdata (struct hid_device*) ; 
 int input_mt_init_slots (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mt_post_parse (struct mt_device*,struct mt_application*) ; 
 int /*<<< orphan*/  mt_post_parse_default_settings (struct mt_device*,struct mt_application*) ; 

__attribute__((used)) static int mt_touch_input_configured(struct hid_device *hdev,
				     struct hid_input *hi,
				     struct mt_application *app)
{
	struct mt_device *td = hid_get_drvdata(hdev);
	struct mt_class *cls = &td->mtclass;
	struct input_dev *input = hi->input;
	int ret;

	if (!td->maxcontacts)
		td->maxcontacts = MT_DEFAULT_MAXCONTACT;

	mt_post_parse(td, app);
	if (td->serial_maybe)
		mt_post_parse_default_settings(td, app);

	if (cls->is_indirect)
		app->mt_flags |= INPUT_MT_POINTER;

	if (app->quirks & MT_QUIRK_NOT_SEEN_MEANS_UP)
		app->mt_flags |= INPUT_MT_DROP_UNUSED;

	/* check for clickpads */
	if ((app->mt_flags & INPUT_MT_POINTER) &&
	    (app->buttons_count == 1))
		td->is_buttonpad = true;

	if (td->is_buttonpad)
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	app->pending_palm_slots = devm_kcalloc(&hi->input->dev,
					       BITS_TO_LONGS(td->maxcontacts),
					       sizeof(long),
					       GFP_KERNEL);
	if (!app->pending_palm_slots)
		return -ENOMEM;

	ret = input_mt_init_slots(input, td->maxcontacts, app->mt_flags);
	if (ret)
		return ret;

	app->mt_flags = 0;
	return 0;
}