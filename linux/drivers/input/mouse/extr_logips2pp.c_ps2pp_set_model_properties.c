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
struct psmouse {char* name; struct input_dev* dev; } ;
struct ps2pp_info {int features; int kind; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  BTN_TASK ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int PS2PP_EXTRA_BTN ; 
 int PS2PP_HWHEEL ; 
#define  PS2PP_KIND_MX 131 
#define  PS2PP_KIND_TP3 130 
#define  PS2PP_KIND_TRACKMAN 129 
#define  PS2PP_KIND_WHEEL 128 
 int PS2PP_NAV_BTN ; 
 int PS2PP_SIDE_BTN ; 
 int PS2PP_TASK_BTN ; 
 int PS2PP_WHEEL ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps2pp_set_model_properties(struct psmouse *psmouse,
				       const struct ps2pp_info *model_info,
				       bool using_ps2pp)
{
	struct input_dev *input_dev = psmouse->dev;

	if (model_info->features & PS2PP_SIDE_BTN)
		input_set_capability(input_dev, EV_KEY, BTN_SIDE);

	if (model_info->features & PS2PP_EXTRA_BTN)
		input_set_capability(input_dev, EV_KEY, BTN_EXTRA);

	if (model_info->features & PS2PP_TASK_BTN)
		input_set_capability(input_dev, EV_KEY, BTN_TASK);

	if (model_info->features & PS2PP_NAV_BTN) {
		input_set_capability(input_dev, EV_KEY, BTN_FORWARD);
		input_set_capability(input_dev, EV_KEY, BTN_BACK);
	}

	if (model_info->features & PS2PP_WHEEL)
		input_set_capability(input_dev, EV_REL, REL_WHEEL);

	if (model_info->features & PS2PP_HWHEEL)
		input_set_capability(input_dev, EV_REL, REL_HWHEEL);

	switch (model_info->kind) {

	case PS2PP_KIND_WHEEL:
		psmouse->name = "Wheel Mouse";
		break;

	case PS2PP_KIND_MX:
		psmouse->name = "MX Mouse";
		break;

	case PS2PP_KIND_TP3:
		psmouse->name = "TouchPad 3";
		break;

	case PS2PP_KIND_TRACKMAN:
		psmouse->name = "TrackMan";
		break;

	default:
		/*
		 * Set name to "Mouse" only when using PS2++,
		 * otherwise let other protocols define suitable
		 * name
		 */
		if (using_ps2pp)
			psmouse->name = "Mouse";
		break;
	}
}