#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct serio_driver {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; TYPE_2__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_4__ dev; TYPE_3__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; scalar_t__ offset; scalar_t__ ibuf; } ;
struct fsia6b {struct input_dev* dev; int /*<<< orphan*/  phys; TYPE_1__ packet; } ;

/* Variables and functions */
 scalar_t__ BTN_0 ; 
 int /*<<< orphan*/  BUS_RS232 ; 
 int /*<<< orphan*/  DRIVER_DESC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IBUS_SERVO_COUNT ; 
 int /*<<< orphan*/  SERIO_FSIA6B ; 
 int /*<<< orphan*/  SYNC ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/ * fsia6b_axes ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct fsia6b*) ; 
 struct fsia6b* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct fsia6b*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 char* switch_config ; 

__attribute__((used)) static int fsia6b_serio_connect(struct serio *serio, struct serio_driver *drv)
{
	struct fsia6b *fsia6b;
	struct input_dev *input_dev;
	int err;
	int i, j;
	int sw_id = 0;

	fsia6b = kzalloc(sizeof(*fsia6b), GFP_KERNEL);
	if (!fsia6b)
		return -ENOMEM;

	fsia6b->packet.ibuf = 0;
	fsia6b->packet.offset = 0;
	fsia6b->packet.state = SYNC;

	serio_set_drvdata(serio, fsia6b);

	input_dev = input_allocate_device();
	if (!input_dev) {
		err = -ENOMEM;
		goto fail1;
	}
	fsia6b->dev = input_dev;

	snprintf(fsia6b->phys, sizeof(fsia6b->phys), "%s/input0", serio->phys);

	input_dev->name = DRIVER_DESC;
	input_dev->phys = fsia6b->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.vendor = SERIO_FSIA6B;
	input_dev->id.product = serio->id.id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &serio->dev;

	for (i = 0; i < IBUS_SERVO_COUNT; i++)
		input_set_abs_params(input_dev, fsia6b_axes[i],
				     1000, 2000, 2, 2);

	/* Register switch configuration */
	for (i = 0; i < IBUS_SERVO_COUNT; i++) {
		if (switch_config[i] < '0' || switch_config[i] > '3') {
			dev_err(&fsia6b->dev->dev,
				"Invalid switch configuration supplied for fsia6b.\n");
			err = -EINVAL;
			goto fail2;
		}

		for (j = '1'; j <= switch_config[i]; j++) {
			input_set_capability(input_dev, EV_KEY, BTN_0 + sw_id);
			sw_id++;
		}
	}

	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	err = input_register_device(fsia6b->dev);
	if (err)
		goto fail3;

	return 0;

fail3:	serio_close(serio);
fail2:	input_free_device(input_dev);
fail1:	serio_set_drvdata(serio, NULL);
	kfree(fsia6b);
	return err;
}