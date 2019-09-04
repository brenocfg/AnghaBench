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
struct serio_driver {int dummy; } ;
struct serio {char* phys; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int version; scalar_t__ product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct egalax {int /*<<< orphan*/  phys; struct input_dev* input; struct serio* serio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_RS232 ; 
 int /*<<< orphan*/  EGALAX_MAX_XC ; 
 int /*<<< orphan*/  EGALAX_MAX_YC ; 
 int /*<<< orphan*/  EGALAX_MIN_XC ; 
 int /*<<< orphan*/  EGALAX_MIN_YC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIO_EGALAX ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct egalax*) ; 
 struct egalax* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct egalax*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int egalax_connect(struct serio *serio, struct serio_driver *drv)
{
	struct egalax *egalax;
	struct input_dev *input_dev;
	int error;

	egalax = kzalloc(sizeof(struct egalax), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!egalax || !input_dev) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	egalax->serio = serio;
	egalax->input = input_dev;
	snprintf(egalax->phys, sizeof(egalax->phys),
		 "%s/input0", serio->phys);

	input_dev->name = "EETI eGalaxTouch Serial TouchScreen";
	input_dev->phys = egalax->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.vendor = SERIO_EGALAX;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0001;
	input_dev->dev.parent = &serio->dev;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_params(input_dev, ABS_X,
			     EGALAX_MIN_XC, EGALAX_MAX_XC, 0, 0);
	input_set_abs_params(input_dev, ABS_Y,
			     EGALAX_MIN_YC, EGALAX_MAX_YC, 0, 0);

	serio_set_drvdata(serio, egalax);

	error = serio_open(serio, drv);
	if (error)
		goto err_reset_drvdata;

	error = input_register_device(input_dev);
	if (error)
		goto err_close_serio;

	return 0;

err_close_serio:
	serio_close(serio);
err_reset_drvdata:
	serio_set_drvdata(serio, NULL);
err_free_mem:
	input_free_device(input_dev);
	kfree(egalax);
	return error;
}