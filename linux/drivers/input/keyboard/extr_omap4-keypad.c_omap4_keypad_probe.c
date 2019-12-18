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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct omap4_keypad {int irq; int reg_offset; int irqreg_offset; unsigned int row_shift; unsigned int rows; scalar_t__ base; struct omap4_keypad* keymap; struct input_dev* input; int /*<<< orphan*/  cols; int /*<<< orphan*/  no_autorepeat; } ;
struct TYPE_4__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ id; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
#define  KBD_REVISION_OMAP4 129 
#define  KBD_REVISION_OMAP5 128 
 int /*<<< orphan*/  MSC_SCAN ; 
 scalar_t__ OMAP4_KBD_REVISION ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (int,struct omap4_keypad*) ; 
 unsigned int get_count_order (int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct omap4_keypad*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct omap4_keypad* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap4_keypad*) ; 
 struct omap4_keypad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,struct omap4_keypad*,struct input_dev*) ; 
 int /*<<< orphan*/  omap4_keypad_close ; 
 int /*<<< orphan*/  omap4_keypad_irq_handler ; 
 int /*<<< orphan*/  omap4_keypad_irq_thread_fn ; 
 int /*<<< orphan*/  omap4_keypad_open ; 
 int omap4_keypad_parse_dt (int /*<<< orphan*/ *,struct omap4_keypad*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap4_keypad*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct omap4_keypad*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int omap4_keypad_probe(struct platform_device *pdev)
{
	struct omap4_keypad *keypad_data;
	struct input_dev *input_dev;
	struct resource *res;
	unsigned int max_keys;
	int rev;
	int irq;
	int error;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no base address specified\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (!irq) {
		dev_err(&pdev->dev, "no keyboard irq assigned\n");
		return -EINVAL;
	}

	keypad_data = kzalloc(sizeof(struct omap4_keypad), GFP_KERNEL);
	if (!keypad_data) {
		dev_err(&pdev->dev, "keypad_data memory allocation failed\n");
		return -ENOMEM;
	}

	keypad_data->irq = irq;

	error = omap4_keypad_parse_dt(&pdev->dev, keypad_data);
	if (error)
		goto err_free_keypad;

	res = request_mem_region(res->start, resource_size(res), pdev->name);
	if (!res) {
		dev_err(&pdev->dev, "can't request mem region\n");
		error = -EBUSY;
		goto err_free_keypad;
	}

	keypad_data->base = ioremap(res->start, resource_size(res));
	if (!keypad_data->base) {
		dev_err(&pdev->dev, "can't ioremap mem resource\n");
		error = -ENOMEM;
		goto err_release_mem;
	}


	/*
	 * Enable clocks for the keypad module so that we can read
	 * revision register.
	 */
	pm_runtime_enable(&pdev->dev);
	error = pm_runtime_get_sync(&pdev->dev);
	if (error) {
		dev_err(&pdev->dev, "pm_runtime_get_sync() failed\n");
		goto err_unmap;
	}
	rev = __raw_readl(keypad_data->base + OMAP4_KBD_REVISION);
	rev &= 0x03 << 30;
	rev >>= 30;
	switch (rev) {
	case KBD_REVISION_OMAP4:
		keypad_data->reg_offset = 0x00;
		keypad_data->irqreg_offset = 0x00;
		break;
	case KBD_REVISION_OMAP5:
		keypad_data->reg_offset = 0x10;
		keypad_data->irqreg_offset = 0x0c;
		break;
	default:
		dev_err(&pdev->dev,
			"Keypad reports unsupported revision %d", rev);
		error = -EINVAL;
		goto err_pm_put_sync;
	}

	/* input device allocation */
	keypad_data->input = input_dev = input_allocate_device();
	if (!input_dev) {
		error = -ENOMEM;
		goto err_pm_put_sync;
	}

	input_dev->name = pdev->name;
	input_dev->dev.parent = &pdev->dev;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendor = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0001;

	input_dev->open = omap4_keypad_open;
	input_dev->close = omap4_keypad_close;

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	if (!keypad_data->no_autorepeat)
		__set_bit(EV_REP, input_dev->evbit);

	input_set_drvdata(input_dev, keypad_data);

	keypad_data->row_shift = get_count_order(keypad_data->cols);
	max_keys = keypad_data->rows << keypad_data->row_shift;
	keypad_data->keymap = kcalloc(max_keys,
				      sizeof(keypad_data->keymap[0]),
				      GFP_KERNEL);
	if (!keypad_data->keymap) {
		dev_err(&pdev->dev, "Not enough memory for keymap\n");
		error = -ENOMEM;
		goto err_free_input;
	}

	error = matrix_keypad_build_keymap(NULL, NULL,
					   keypad_data->rows, keypad_data->cols,
					   keypad_data->keymap, input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		goto err_free_keymap;
	}

	error = request_threaded_irq(keypad_data->irq, omap4_keypad_irq_handler,
				     omap4_keypad_irq_thread_fn, IRQF_ONESHOT,
				     "omap4-keypad", keypad_data);
	if (error) {
		dev_err(&pdev->dev, "failed to register interrupt\n");
		goto err_free_keymap;
	}

	device_init_wakeup(&pdev->dev, true);
	pm_runtime_put_sync(&pdev->dev);

	error = input_register_device(keypad_data->input);
	if (error < 0) {
		dev_err(&pdev->dev, "failed to register input device\n");
		goto err_pm_disable;
	}

	platform_set_drvdata(pdev, keypad_data);
	return 0;

err_pm_disable:
	pm_runtime_disable(&pdev->dev);
	free_irq(keypad_data->irq, keypad_data);
err_free_keymap:
	kfree(keypad_data->keymap);
err_free_input:
	input_free_device(input_dev);
err_pm_put_sync:
	pm_runtime_put_sync(&pdev->dev);
err_unmap:
	iounmap(keypad_data->base);
err_release_mem:
	release_mem_region(res->start, resource_size(res));
err_free_keypad:
	kfree(keypad_data);
	return error;
}