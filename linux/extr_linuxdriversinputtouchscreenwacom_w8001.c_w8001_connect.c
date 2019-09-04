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
struct w8001 {char* pen_name; char* touch_name; struct input_dev* pen_dev; struct input_dev* touch_dev; int /*<<< orphan*/  phys; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  mutex; struct serio* serio; } ;
struct serio_driver {int dummy; } ;
struct serio {char* phys; } ;
struct input_dev {char* name; } ;
typedef  int /*<<< orphan*/  basename ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct w8001*) ; 
 struct w8001* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct w8001*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int w8001_detect (struct w8001*) ; 
 int /*<<< orphan*/  w8001_set_devdata (struct input_dev*,struct w8001*,struct serio*) ; 
 int w8001_setup_pen (struct w8001*,char*,int) ; 
 int w8001_setup_touch (struct w8001*,char*,int) ; 

__attribute__((used)) static int w8001_connect(struct serio *serio, struct serio_driver *drv)
{
	struct w8001 *w8001;
	struct input_dev *input_dev_pen;
	struct input_dev *input_dev_touch;
	char basename[64];
	int err, err_pen, err_touch;

	w8001 = kzalloc(sizeof(struct w8001), GFP_KERNEL);
	input_dev_pen = input_allocate_device();
	input_dev_touch = input_allocate_device();
	if (!w8001 || !input_dev_pen || !input_dev_touch) {
		err = -ENOMEM;
		goto fail1;
	}

	w8001->serio = serio;
	w8001->pen_dev = input_dev_pen;
	w8001->touch_dev = input_dev_touch;
	mutex_init(&w8001->mutex);
	init_completion(&w8001->cmd_done);
	snprintf(w8001->phys, sizeof(w8001->phys), "%s/input0", serio->phys);

	serio_set_drvdata(serio, w8001);
	err = serio_open(serio, drv);
	if (err)
		goto fail2;

	err = w8001_detect(w8001);
	if (err)
		goto fail3;

	/* For backwards-compatibility we compose the basename based on
	 * capabilities and then just append the tool type
	 */
	strlcpy(basename, "Wacom Serial", sizeof(basename));

	err_pen = w8001_setup_pen(w8001, basename, sizeof(basename));
	err_touch = w8001_setup_touch(w8001, basename, sizeof(basename));
	if (err_pen && err_touch) {
		err = -ENXIO;
		goto fail3;
	}

	if (!err_pen) {
		strlcpy(w8001->pen_name, basename, sizeof(w8001->pen_name));
		strlcat(w8001->pen_name, " Pen", sizeof(w8001->pen_name));
		input_dev_pen->name = w8001->pen_name;

		w8001_set_devdata(input_dev_pen, w8001, serio);

		err = input_register_device(w8001->pen_dev);
		if (err)
			goto fail3;
	} else {
		input_free_device(input_dev_pen);
		input_dev_pen = NULL;
		w8001->pen_dev = NULL;
	}

	if (!err_touch) {
		strlcpy(w8001->touch_name, basename, sizeof(w8001->touch_name));
		strlcat(w8001->touch_name, " Finger",
			sizeof(w8001->touch_name));
		input_dev_touch->name = w8001->touch_name;

		w8001_set_devdata(input_dev_touch, w8001, serio);

		err = input_register_device(w8001->touch_dev);
		if (err)
			goto fail4;
	} else {
		input_free_device(input_dev_touch);
		input_dev_touch = NULL;
		w8001->touch_dev = NULL;
	}

	return 0;

fail4:
	if (w8001->pen_dev)
		input_unregister_device(w8001->pen_dev);
fail3:
	serio_close(serio);
fail2:
	serio_set_drvdata(serio, NULL);
fail1:
	input_free_device(input_dev_pen);
	input_free_device(input_dev_touch);
	kfree(w8001);
	return err;
}