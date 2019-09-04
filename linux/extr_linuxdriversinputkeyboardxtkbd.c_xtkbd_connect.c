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
struct xtkbd {struct input_dev* dev; int /*<<< orphan*/ * keycode; int /*<<< orphan*/  phys; struct serio* serio; } ;
struct serio_driver {int dummy; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int* evbit; int keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  keycodemax; int /*<<< orphan*/ * keycode; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_XTKBD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct xtkbd*) ; 
 struct xtkbd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct xtkbd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  xtkbd_keycode ; 

__attribute__((used)) static int xtkbd_connect(struct serio *serio, struct serio_driver *drv)
{
	struct xtkbd *xtkbd;
	struct input_dev *input_dev;
	int err = -ENOMEM;
	int i;

	xtkbd = kmalloc(sizeof(struct xtkbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!xtkbd || !input_dev)
		goto fail1;

	xtkbd->serio = serio;
	xtkbd->dev = input_dev;
	snprintf(xtkbd->phys, sizeof(xtkbd->phys), "%s/input0", serio->phys);
	memcpy(xtkbd->keycode, xtkbd_keycode, sizeof(xtkbd->keycode));

	input_dev->name = "XT Keyboard";
	input_dev->phys = xtkbd->phys;
	input_dev->id.bustype = BUS_XTKBD;
	input_dev->id.vendor  = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycode = xtkbd->keycode;
	input_dev->keycodesize = sizeof(unsigned char);
	input_dev->keycodemax = ARRAY_SIZE(xtkbd_keycode);

	for (i = 0; i < 255; i++)
		set_bit(xtkbd->keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	serio_set_drvdata(serio, xtkbd);

	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	err = input_register_device(xtkbd->dev);
	if (err)
		goto fail3;

	return 0;

 fail3:	serio_close(serio);
 fail2:	serio_set_drvdata(serio, NULL);
 fail1:	input_free_device(input_dev);
	kfree(xtkbd);
	return err;
}