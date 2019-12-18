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
struct skbd {struct input_dev* dev; int /*<<< orphan*/  keycode; int /*<<< orphan*/  phys; struct serio* serio; } ;
struct serio_driver {int dummy; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int product; int version; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int* evbit; int keycodesize; int keycodemax; int /*<<< orphan*/  keybit; int /*<<< orphan*/  keycode; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_RS232 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIO_STOWAWAY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct skbd*) ; 
 struct skbd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct skbd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skbd_keycode ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int skbd_connect(struct serio *serio, struct serio_driver *drv)
{
	struct skbd *skbd;
	struct input_dev *input_dev;
	int err = -ENOMEM;
	int i;

	skbd = kzalloc(sizeof(struct skbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!skbd || !input_dev)
		goto fail1;

	skbd->serio = serio;
	skbd->dev = input_dev;
	snprintf(skbd->phys, sizeof(skbd->phys), "%s/input0", serio->phys);
	memcpy(skbd->keycode, skbd_keycode, sizeof(skbd->keycode));

	input_dev->name = "Stowaway Keyboard";
	input_dev->phys = skbd->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.vendor = SERIO_STOWAWAY;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycode = skbd->keycode;
	input_dev->keycodesize = sizeof(unsigned char);
	input_dev->keycodemax = ARRAY_SIZE(skbd_keycode);
	for (i = 0; i < ARRAY_SIZE(skbd_keycode); i++)
		set_bit(skbd_keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	serio_set_drvdata(serio, skbd);

	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	err = input_register_device(skbd->dev);
	if (err)
		goto fail3;

	return 0;

 fail3: serio_close(serio);
 fail2:	serio_set_drvdata(serio, NULL);
 fail1:	input_free_device(input_dev);
	kfree(skbd);
	return err;
}