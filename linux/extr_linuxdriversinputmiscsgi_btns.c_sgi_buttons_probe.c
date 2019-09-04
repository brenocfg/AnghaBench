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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct input_polled_dev {struct input_dev* input; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; struct buttons_dev* private; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; int keycodemax; int keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/ * keycode; TYPE_2__ dev; TYPE_1__ id; } ;
struct buttons_dev {struct input_polled_dev* poll_dev; int /*<<< orphan*/ * keymap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int /*<<< orphan*/  BUTTONS_POLL_INTERVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_buttons ; 
 struct input_polled_dev* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (struct input_polled_dev*) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buttons_dev*) ; 
 struct buttons_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct buttons_dev*) ; 
 int /*<<< orphan*/ * sgi_map ; 

__attribute__((used)) static int sgi_buttons_probe(struct platform_device *pdev)
{
	struct buttons_dev *bdev;
	struct input_polled_dev *poll_dev;
	struct input_dev *input;
	int error, i;

	bdev = kzalloc(sizeof(struct buttons_dev), GFP_KERNEL);
	poll_dev = input_allocate_polled_device();
	if (!bdev || !poll_dev) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	memcpy(bdev->keymap, sgi_map, sizeof(bdev->keymap));

	poll_dev->private = bdev;
	poll_dev->poll = handle_buttons;
	poll_dev->poll_interval = BUTTONS_POLL_INTERVAL;

	input = poll_dev->input;
	input->name = "SGI buttons";
	input->phys = "sgi/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = &pdev->dev;

	input->keycode = bdev->keymap;
	input->keycodemax = ARRAY_SIZE(bdev->keymap);
	input->keycodesize = sizeof(unsigned short);

	input_set_capability(input, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input->evbit);
	for (i = 0; i < ARRAY_SIZE(sgi_map); i++)
		__set_bit(bdev->keymap[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	bdev->poll_dev = poll_dev;
	platform_set_drvdata(pdev, bdev);

	error = input_register_polled_device(poll_dev);
	if (error)
		goto err_free_mem;

	return 0;

 err_free_mem:
	input_free_polled_device(poll_dev);
	kfree(bdev);
	return error;
}