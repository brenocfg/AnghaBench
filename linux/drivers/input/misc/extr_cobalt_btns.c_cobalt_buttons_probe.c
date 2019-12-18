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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct input_polled_dev {struct input_dev* input; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; struct buttons_dev* private; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; int keycodemax; int keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/ * keycode; TYPE_2__ dev; TYPE_1__ id; } ;
struct buttons_dev {int /*<<< orphan*/  reg; struct input_polled_dev* poll_dev; int /*<<< orphan*/ * keymap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int /*<<< orphan*/  BUTTONS_POLL_INTERVAL ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cobalt_map ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct buttons_dev*) ; 
 int /*<<< orphan*/  handle_buttons ; 
 struct input_polled_dev* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (struct input_polled_dev*) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buttons_dev*) ; 
 struct buttons_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int cobalt_buttons_probe(struct platform_device *pdev)
{
	struct buttons_dev *bdev;
	struct input_polled_dev *poll_dev;
	struct input_dev *input;
	struct resource *res;
	int error, i;

	bdev = kzalloc(sizeof(struct buttons_dev), GFP_KERNEL);
	poll_dev = input_allocate_polled_device();
	if (!bdev || !poll_dev) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	memcpy(bdev->keymap, cobalt_map, sizeof(bdev->keymap));

	poll_dev->private = bdev;
	poll_dev->poll = handle_buttons;
	poll_dev->poll_interval = BUTTONS_POLL_INTERVAL;

	input = poll_dev->input;
	input->name = "Cobalt buttons";
	input->phys = "cobalt/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = &pdev->dev;

	input->keycode = bdev->keymap;
	input->keycodemax = ARRAY_SIZE(bdev->keymap);
	input->keycodesize = sizeof(unsigned short);

	input_set_capability(input, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input->evbit);
	for (i = 0; i < ARRAY_SIZE(cobalt_map); i++)
		__set_bit(bdev->keymap[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		error = -EBUSY;
		goto err_free_mem;
	}

	bdev->poll_dev = poll_dev;
	bdev->reg = ioremap(res->start, resource_size(res));
	dev_set_drvdata(&pdev->dev, bdev);

	error = input_register_polled_device(poll_dev);
	if (error)
		goto err_iounmap;

	return 0;

 err_iounmap:
	iounmap(bdev->reg);
 err_free_mem:
	input_free_polled_device(poll_dev);
	kfree(bdev);
	return error;
}