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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct vmmouse_data {struct input_dev* abs_dev; } ;
struct psmouse {struct vmmouse_data* private; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABSPOINTER_DATA ; 
 int /*<<< orphan*/  ABSPOINTER_STATUS ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  VMMOUSE_CMD (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int VMMOUSE_ERROR ; 
 int VMMOUSE_LEFT_BUTTON ; 
 int VMMOUSE_MIDDLE_BUTTON ; 
 int VMMOUSE_RELATIVE_PACKET ; 
 int VMMOUSE_RIGHT_BUTTON ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  vmmouse_report_button (struct psmouse*,struct input_dev*,struct input_dev*,struct input_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static psmouse_ret_t vmmouse_report_events(struct psmouse *psmouse)
{
	struct input_dev *rel_dev = psmouse->dev;
	struct vmmouse_data *priv = psmouse->private;
	struct input_dev *abs_dev = priv->abs_dev;
	struct input_dev *pref_dev;
	u32 status, x, y, z;
	u32 dummy1, dummy2, dummy3;
	unsigned int queue_length;
	unsigned int count = 255;

	while (count--) {
		/* See if we have motion data. */
		VMMOUSE_CMD(ABSPOINTER_STATUS, 0,
			    status, dummy1, dummy2, dummy3);
		if ((status & VMMOUSE_ERROR) == VMMOUSE_ERROR) {
			psmouse_err(psmouse, "failed to fetch status data\n");
			/*
			 * After a few attempts this will result in
			 * reconnect.
			 */
			return PSMOUSE_BAD_DATA;
		}

		queue_length = status & 0xffff;
		if (queue_length == 0)
			break;

		if (queue_length % 4) {
			psmouse_err(psmouse, "invalid queue length\n");
			return PSMOUSE_BAD_DATA;
		}

		/* Now get it */
		VMMOUSE_CMD(ABSPOINTER_DATA, 4, status, x, y, z);

		/*
		 * And report what we've got. Prefer to report button
		 * events on the same device where we report motion events.
		 * This doesn't work well with the mouse wheel, though. See
		 * below. Ideally we would want to report that on the
		 * preferred device as well.
		 */
		if (status & VMMOUSE_RELATIVE_PACKET) {
			pref_dev = rel_dev;
			input_report_rel(rel_dev, REL_X, (s32)x);
			input_report_rel(rel_dev, REL_Y, -(s32)y);
		} else {
			pref_dev = abs_dev;
			input_report_abs(abs_dev, ABS_X, x);
			input_report_abs(abs_dev, ABS_Y, y);
		}

		/* Xorg seems to ignore wheel events on absolute devices */
		input_report_rel(rel_dev, REL_WHEEL, -(s8)((u8) z));

		vmmouse_report_button(psmouse, abs_dev, rel_dev,
				      pref_dev, BTN_LEFT,
				      status & VMMOUSE_LEFT_BUTTON);
		vmmouse_report_button(psmouse, abs_dev, rel_dev,
				      pref_dev, BTN_RIGHT,
				      status & VMMOUSE_RIGHT_BUTTON);
		vmmouse_report_button(psmouse, abs_dev, rel_dev,
				      pref_dev, BTN_MIDDLE,
				      status & VMMOUSE_MIDDLE_BUTTON);
		input_sync(abs_dev);
		input_sync(rel_dev);
	}

	return PSMOUSE_FULL_PACKET;
}