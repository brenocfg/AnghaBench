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
struct pxa930_rotary_platform_data {scalar_t__ rel_code; scalar_t__ down_key; scalar_t__ up_key; } ;
struct pxa930_rotary {int /*<<< orphan*/ * mmio_base; struct input_dev* input_dev; struct pxa930_rotary_platform_data* pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  evbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ EV_KEY ; 
 scalar_t__ EV_REL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pxa930_rotary_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct pxa930_rotary*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct pxa930_rotary*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pxa930_rotary*) ; 
 struct pxa930_rotary* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxa930_rotary*) ; 
 int /*<<< orphan*/  pxa930_rotary_close ; 
 int /*<<< orphan*/  pxa930_rotary_open ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pxa930_rotary*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  rotary_irq ; 

__attribute__((used)) static int pxa930_rotary_probe(struct platform_device *pdev)
{
	struct pxa930_rotary_platform_data *pdata =
			dev_get_platdata(&pdev->dev);
	struct pxa930_rotary *r;
	struct input_dev *input_dev;
	struct resource *res;
	int irq;
	int err;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -ENXIO;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no I/O memory defined\n");
		return -ENXIO;
	}

	if (!pdata) {
		dev_err(&pdev->dev, "no platform data defined\n");
		return -EINVAL;
	}

	r = kzalloc(sizeof(struct pxa930_rotary), GFP_KERNEL);
	if (!r)
		return -ENOMEM;

	r->mmio_base = ioremap_nocache(res->start, resource_size(res));
	if (r->mmio_base == NULL) {
		dev_err(&pdev->dev, "failed to remap IO memory\n");
		err = -ENXIO;
		goto failed_free;
	}

	r->pdata = pdata;
	platform_set_drvdata(pdev, r);

	/* allocate and register the input device */
	input_dev = input_allocate_device();
	if (!input_dev) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		err = -ENOMEM;
		goto failed_free_io;
	}

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->open = pxa930_rotary_open;
	input_dev->close = pxa930_rotary_close;
	input_dev->dev.parent = &pdev->dev;

	if (pdata->up_key && pdata->down_key) {
		__set_bit(pdata->up_key, input_dev->keybit);
		__set_bit(pdata->down_key, input_dev->keybit);
		__set_bit(EV_KEY, input_dev->evbit);
	} else {
		__set_bit(pdata->rel_code, input_dev->relbit);
		__set_bit(EV_REL, input_dev->evbit);
	}

	r->input_dev = input_dev;
	input_set_drvdata(input_dev, r);

	err = request_irq(irq, rotary_irq, 0,
			"enhanced rotary", r);
	if (err) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		goto failed_free_input;
	}

	err = input_register_device(input_dev);
	if (err) {
		dev_err(&pdev->dev, "failed to register input device\n");
		goto failed_free_irq;
	}

	return 0;

failed_free_irq:
	free_irq(irq, r);
failed_free_input:
	input_free_device(input_dev);
failed_free_io:
	iounmap(r->mmio_base);
failed_free:
	kfree(r);
	return err;
}