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
struct vsxxxaa {int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct serio* serio; struct input_dev* dev; } ;
struct serio_driver {int dummy; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_RS232 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vsxxxaa*) ; 
 struct vsxxxaa* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct vsxxxaa*) ; 
 int /*<<< orphan*/  serio_write (struct serio*,char) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vsxxxaa_connect(struct serio *serio, struct serio_driver *drv)
{
	struct vsxxxaa *mouse;
	struct input_dev *input_dev;
	int err = -ENOMEM;

	mouse = kzalloc(sizeof(struct vsxxxaa), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!mouse || !input_dev)
		goto fail1;

	mouse->dev = input_dev;
	mouse->serio = serio;
	strlcat(mouse->name, "DEC VSXXX-AA/-GA mouse or VSXXX-AB digitizer",
		 sizeof(mouse->name));
	snprintf(mouse->phys, sizeof(mouse->phys), "%s/input0", serio->phys);

	input_dev->name = mouse->name;
	input_dev->phys = mouse->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->dev.parent = &serio->dev;

	__set_bit(EV_KEY, input_dev->evbit);		/* We have buttons */
	__set_bit(EV_REL, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(BTN_LEFT, input_dev->keybit);		/* We have 3 buttons */
	__set_bit(BTN_MIDDLE, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_TOUCH, input_dev->keybit);	/* ...and Tablet */
	__set_bit(REL_X, input_dev->relbit);
	__set_bit(REL_Y, input_dev->relbit);
	input_set_abs_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 1023, 0, 0);

	serio_set_drvdata(serio, mouse);

	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	/*
	 * Request selftest. Standard packet format and differential
	 * mode will be requested after the device ID'ed successfully.
	 */
	serio_write(serio, 'T'); /* Test */

	err = input_register_device(input_dev);
	if (err)
		goto fail3;

	return 0;

 fail3:	serio_close(serio);
 fail2:	serio_set_drvdata(serio, NULL);
 fail1:	input_free_device(input_dev);
	kfree(mouse);
	return err;
}