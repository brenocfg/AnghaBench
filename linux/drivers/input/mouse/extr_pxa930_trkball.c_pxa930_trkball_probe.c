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
struct pxa930_trkball {int /*<<< orphan*/  mmio_base; struct input_dev* input; int /*<<< orphan*/  pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct pxa930_trkball*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct pxa930_trkball*) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxa930_trkball*) ; 
 struct pxa930_trkball* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxa930_trkball*) ; 
 int /*<<< orphan*/  pxa930_trkball_close ; 
 int /*<<< orphan*/  pxa930_trkball_disable (struct pxa930_trkball*) ; 
 int /*<<< orphan*/  pxa930_trkball_interrupt ; 
 int /*<<< orphan*/  pxa930_trkball_open ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pxa930_trkball*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int pxa930_trkball_probe(struct platform_device *pdev)
{
	struct pxa930_trkball *trkball;
	struct input_dev *input;
	struct resource *res;
	int irq, error;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -ENXIO;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to get register memory\n");
		return -ENXIO;
	}

	trkball = kzalloc(sizeof(struct pxa930_trkball), GFP_KERNEL);
	if (!trkball)
		return -ENOMEM;

	trkball->pdata = dev_get_platdata(&pdev->dev);
	if (!trkball->pdata) {
		dev_err(&pdev->dev, "no platform data defined\n");
		error = -EINVAL;
		goto failed;
	}

	trkball->mmio_base = ioremap_nocache(res->start, resource_size(res));
	if (!trkball->mmio_base) {
		dev_err(&pdev->dev, "failed to ioremap registers\n");
		error = -ENXIO;
		goto failed;
	}

	/* held the module in reset, will be enabled in open() */
	pxa930_trkball_disable(trkball);

	error = request_irq(irq, pxa930_trkball_interrupt, 0,
			    pdev->name, trkball);
	if (error) {
		dev_err(&pdev->dev, "failed to request irq: %d\n", error);
		goto failed_free_io;
	}

	platform_set_drvdata(pdev, trkball);

	input = input_allocate_device();
	if (!input) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		error = -ENOMEM;
		goto failed_free_irq;
	}

	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input->open = pxa930_trkball_open;
	input->close = pxa930_trkball_close;
	input->dev.parent = &pdev->dev;
	input_set_drvdata(input, trkball);

	trkball->input = input;

	input_set_capability(input, EV_REL, REL_X);
	input_set_capability(input, EV_REL, REL_Y);

	error = input_register_device(input);
	if (error) {
		dev_err(&pdev->dev, "unable to register input device\n");
		goto failed_free_input;
	}

	return 0;

failed_free_input:
	input_free_device(input);
failed_free_irq:
	free_irq(irq, trkball);
failed_free_io:
	iounmap(trkball->mmio_base);
failed:
	kfree(trkball);
	return error;
}