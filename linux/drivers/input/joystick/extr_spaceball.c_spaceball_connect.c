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
struct spaceball {struct input_dev* dev; int /*<<< orphan*/  phys; } ;
struct serio_driver {int dummy; } ;
struct TYPE_4__ {int id; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; TYPE_1__ id; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int product; int version; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {int* evbit; int* keybit; TYPE_3__ dev; TYPE_2__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ABS_RX ; 
 scalar_t__ ABS_X ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_3 ; 
 int /*<<< orphan*/  BTN_4 ; 
 int /*<<< orphan*/  BTN_5 ; 
 int /*<<< orphan*/  BTN_6 ; 
 int /*<<< orphan*/  BTN_7 ; 
 int /*<<< orphan*/  BTN_8 ; 
 int /*<<< orphan*/  BTN_9 ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_C ; 
 int /*<<< orphan*/  BTN_MODE ; 
 int /*<<< orphan*/  BUS_RS232 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIO_SPACEBALL ; 
#define  SPACEBALL_3003C 130 
#define  SPACEBALL_4000FLX 129 
#define  SPACEBALL_4000FLX_L 128 
 int SPACEBALL_MAX_ID ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct spaceball*) ; 
 struct spaceball* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct spaceball*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/ * spaceball_names ; 

__attribute__((used)) static int spaceball_connect(struct serio *serio, struct serio_driver *drv)
{
	struct spaceball *spaceball;
	struct input_dev *input_dev;
	int err = -ENOMEM;
	int i, id;

	if ((id = serio->id.id) > SPACEBALL_MAX_ID)
		return -ENODEV;

	spaceball = kmalloc(sizeof(struct spaceball), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!spaceball || !input_dev)
		goto fail1;

	spaceball->dev = input_dev;
	snprintf(spaceball->phys, sizeof(spaceball->phys), "%s/input0", serio->phys);

	input_dev->name = spaceball_names[id];
	input_dev->phys = spaceball->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.vendor = SERIO_SPACEBALL;
	input_dev->id.product = id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	switch (id) {
		case SPACEBALL_4000FLX:
		case SPACEBALL_4000FLX_L:
			input_dev->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_9);
			input_dev->keybit[BIT_WORD(BTN_A)] |= BIT_MASK(BTN_A) |
				BIT_MASK(BTN_B) | BIT_MASK(BTN_C) |
				BIT_MASK(BTN_MODE);
			/* fall through */
		default:
			input_dev->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_2) |
				BIT_MASK(BTN_3) | BIT_MASK(BTN_4) |
				BIT_MASK(BTN_5) | BIT_MASK(BTN_6) |
				BIT_MASK(BTN_7) | BIT_MASK(BTN_8);
			/* fall through */
		case SPACEBALL_3003C:
			input_dev->keybit[BIT_WORD(BTN_0)] |= BIT_MASK(BTN_1) |
				BIT_MASK(BTN_8);
	}

	for (i = 0; i < 3; i++) {
		input_set_abs_params(input_dev, ABS_X + i, -8000, 8000, 8, 40);
		input_set_abs_params(input_dev, ABS_RX + i, -1600, 1600, 2, 8);
	}

	serio_set_drvdata(serio, spaceball);

	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	err = input_register_device(spaceball->dev);
	if (err)
		goto fail3;

	return 0;

 fail3:	serio_close(serio);
 fail2:	serio_set_drvdata(serio, NULL);
 fail1:	input_free_device(input_dev);
	kfree(spaceball);
	return err;
}