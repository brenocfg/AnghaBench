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
struct w90p910_keypad_platform_data {struct matrix_keymap_data* keymap_data; } ;
struct w90p910_keypad {int irq; int /*<<< orphan*/ * mmio_base; int /*<<< orphan*/  clk; int /*<<< orphan*/  keymap; struct input_dev* input_dev; struct w90p910_keypad_platform_data const* pdata; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct matrix_keymap_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  evbit; TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W90P910_NUM_COLS ; 
 int /*<<< orphan*/  W90P910_NUM_ROWS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct w90p910_keypad_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct w90p910_keypad*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct w90p910_keypad*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct w90p910_keypad*) ; 
 struct w90p910_keypad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int matrix_keypad_build_keymap (struct matrix_keymap_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_dev*) ; 
 int /*<<< orphan*/  mfp_set_groupi (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct w90p910_keypad*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct w90p910_keypad*) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  w90p910_keypad_close ; 
 int /*<<< orphan*/  w90p910_keypad_irq_handler ; 
 int /*<<< orphan*/  w90p910_keypad_open ; 

__attribute__((used)) static int w90p910_keypad_probe(struct platform_device *pdev)
{
	const struct w90p910_keypad_platform_data *pdata =
						dev_get_platdata(&pdev->dev);
	const struct matrix_keymap_data *keymap_data;
	struct w90p910_keypad *keypad;
	struct input_dev *input_dev;
	struct resource *res;
	int irq;
	int error;

	if (!pdata) {
		dev_err(&pdev->dev, "no platform data defined\n");
		return -EINVAL;
	}

	keymap_data = pdata->keymap_data;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "failed to get keypad irq\n");
		return -ENXIO;
	}

	keypad = kzalloc(sizeof(struct w90p910_keypad), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!keypad || !input_dev) {
		dev_err(&pdev->dev, "failed to allocate driver data\n");
		error = -ENOMEM;
		goto failed_free;
	}

	keypad->pdata = pdata;
	keypad->input_dev = input_dev;
	keypad->irq = irq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "failed to get I/O memory\n");
		error = -ENXIO;
		goto failed_free;
	}

	res = request_mem_region(res->start, resource_size(res), pdev->name);
	if (res == NULL) {
		dev_err(&pdev->dev, "failed to request I/O memory\n");
		error = -EBUSY;
		goto failed_free;
	}

	keypad->mmio_base = ioremap(res->start, resource_size(res));
	if (keypad->mmio_base == NULL) {
		dev_err(&pdev->dev, "failed to remap I/O memory\n");
		error = -ENXIO;
		goto failed_free_res;
	}

	keypad->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(keypad->clk)) {
		dev_err(&pdev->dev, "failed to get keypad clock\n");
		error = PTR_ERR(keypad->clk);
		goto failed_free_io;
	}

	/* set multi-function pin for w90p910 kpi. */
	mfp_set_groupi(&pdev->dev);

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->open = w90p910_keypad_open;
	input_dev->close = w90p910_keypad_close;
	input_dev->dev.parent = &pdev->dev;

	error = matrix_keypad_build_keymap(keymap_data, NULL,
					   W90P910_NUM_ROWS, W90P910_NUM_COLS,
					   keypad->keymap, input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		goto failed_put_clk;
	}

	error = request_irq(keypad->irq, w90p910_keypad_irq_handler,
			    0, pdev->name, keypad);
	if (error) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		goto failed_put_clk;
	}

	__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, keypad);

	/* Register the input device */
	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		goto failed_free_irq;
	}

	platform_set_drvdata(pdev, keypad);
	return 0;

failed_free_irq:
	free_irq(irq, keypad);
failed_put_clk:
	clk_put(keypad->clk);
failed_free_io:
	iounmap(keypad->mmio_base);
failed_free_res:
	release_mem_region(res->start, resource_size(res));
failed_free:
	input_free_device(input_dev);
	kfree(keypad);
	return error;
}