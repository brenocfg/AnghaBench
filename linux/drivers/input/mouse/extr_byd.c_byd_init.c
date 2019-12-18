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
struct psmouse {int pktsize; scalar_t__ resync_time; int /*<<< orphan*/  protocol_handler; int /*<<< orphan*/  reconnect; int /*<<< orphan*/  disconnect; struct byd_data* private; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  relbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  propbit; } ;
struct byd_data {int /*<<< orphan*/  timer; struct psmouse* psmouse; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BYD_PAD_HEIGHT ; 
 int /*<<< orphan*/  BYD_PAD_RESOLUTION ; 
 int /*<<< orphan*/  BYD_PAD_WIDTH ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byd_clear_touch ; 
 int /*<<< orphan*/  byd_disconnect ; 
 int /*<<< orphan*/  byd_process_byte ; 
 int /*<<< orphan*/  byd_reconnect ; 
 scalar_t__ byd_reset_touchpad (struct psmouse*) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct byd_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ psmouse_reset (struct psmouse*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int byd_init(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct byd_data *priv;

	if (psmouse_reset(psmouse))
		return -EIO;

	if (byd_reset_touchpad(psmouse))
		return -EIO;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->psmouse = psmouse;
	timer_setup(&priv->timer, byd_clear_touch, 0);

	psmouse->private = priv;
	psmouse->disconnect = byd_disconnect;
	psmouse->reconnect = byd_reconnect;
	psmouse->protocol_handler = byd_process_byte;
	psmouse->pktsize = 4;
	psmouse->resync_time = 0;

	__set_bit(INPUT_PROP_POINTER, dev->propbit);
	/* Touchpad */
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_FINGER, dev->keybit);
	/* Buttons */
	__set_bit(BTN_LEFT, dev->keybit);
	__set_bit(BTN_RIGHT, dev->keybit);
	__clear_bit(BTN_MIDDLE, dev->keybit);

	/* Absolute position */
	__set_bit(EV_ABS, dev->evbit);
	input_set_abs_params(dev, ABS_X, 0, BYD_PAD_WIDTH, 0, 0);
	input_set_abs_params(dev, ABS_Y, 0, BYD_PAD_HEIGHT, 0, 0);
	input_abs_set_res(dev, ABS_X, BYD_PAD_RESOLUTION);
	input_abs_set_res(dev, ABS_Y, BYD_PAD_RESOLUTION);
	/* No relative support */
	__clear_bit(EV_REL, dev->evbit);
	__clear_bit(REL_X, dev->relbit);
	__clear_bit(REL_Y, dev->relbit);

	return 0;
}