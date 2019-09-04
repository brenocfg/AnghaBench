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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct matrix_keymap_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  evbit; TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct ep93xx_keypad {int /*<<< orphan*/ * mmio_base; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; TYPE_3__* pdata; int /*<<< orphan*/  keycodes; struct input_dev* input_dev; } ;
struct TYPE_6__ {int flags; struct matrix_keymap_data* keymap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EP93XX_KEYPAD_AUTOREPEAT ; 
 int /*<<< orphan*/  EP93XX_MATRIX_COLS ; 
 int /*<<< orphan*/  EP93XX_MATRIX_ROWS ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 TYPE_3__* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int ep93xx_keypad_acquire_gpio (struct platform_device*) ; 
 int /*<<< orphan*/  ep93xx_keypad_close ; 
 int /*<<< orphan*/  ep93xx_keypad_irq_handler ; 
 int /*<<< orphan*/  ep93xx_keypad_open ; 
 int /*<<< orphan*/  ep93xx_keypad_release_gpio (struct platform_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ep93xx_keypad*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct ep93xx_keypad*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ep93xx_keypad*) ; 
 struct ep93xx_keypad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int matrix_keypad_build_keymap (struct matrix_keymap_data const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_dev*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ep93xx_keypad*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ep93xx_keypad*) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ep93xx_keypad_probe(struct platform_device *pdev)
{
	struct ep93xx_keypad *keypad;
	const struct matrix_keymap_data *keymap_data;
	struct input_dev *input_dev;
	struct resource *res;
	int err;

	keypad = kzalloc(sizeof(struct ep93xx_keypad), GFP_KERNEL);
	if (!keypad)
		return -ENOMEM;

	keypad->pdata = dev_get_platdata(&pdev->dev);
	if (!keypad->pdata) {
		err = -EINVAL;
		goto failed_free;
	}

	keymap_data = keypad->pdata->keymap_data;
	if (!keymap_data) {
		err = -EINVAL;
		goto failed_free;
	}

	keypad->irq = platform_get_irq(pdev, 0);
	if (!keypad->irq) {
		err = -ENXIO;
		goto failed_free;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		err = -ENXIO;
		goto failed_free;
	}

	res = request_mem_region(res->start, resource_size(res), pdev->name);
	if (!res) {
		err = -EBUSY;
		goto failed_free;
	}

	keypad->mmio_base = ioremap(res->start, resource_size(res));
	if (keypad->mmio_base == NULL) {
		err = -ENXIO;
		goto failed_free_mem;
	}

	err = ep93xx_keypad_acquire_gpio(pdev);
	if (err)
		goto failed_free_io;

	keypad->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(keypad->clk)) {
		err = PTR_ERR(keypad->clk);
		goto failed_free_gpio;
	}

	input_dev = input_allocate_device();
	if (!input_dev) {
		err = -ENOMEM;
		goto failed_put_clk;
	}

	keypad->input_dev = input_dev;

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->open = ep93xx_keypad_open;
	input_dev->close = ep93xx_keypad_close;
	input_dev->dev.parent = &pdev->dev;

	err = matrix_keypad_build_keymap(keymap_data, NULL,
					 EP93XX_MATRIX_ROWS, EP93XX_MATRIX_COLS,
					 keypad->keycodes, input_dev);
	if (err)
		goto failed_free_dev;

	if (keypad->pdata->flags & EP93XX_KEYPAD_AUTOREPEAT)
		__set_bit(EV_REP, input_dev->evbit);
	input_set_drvdata(input_dev, keypad);

	err = request_irq(keypad->irq, ep93xx_keypad_irq_handler,
			  0, pdev->name, keypad);
	if (err)
		goto failed_free_dev;

	err = input_register_device(input_dev);
	if (err)
		goto failed_free_irq;

	platform_set_drvdata(pdev, keypad);
	device_init_wakeup(&pdev->dev, 1);

	return 0;

failed_free_irq:
	free_irq(keypad->irq, keypad);
failed_free_dev:
	input_free_device(input_dev);
failed_put_clk:
	clk_put(keypad->clk);
failed_free_gpio:
	ep93xx_keypad_release_gpio(pdev);
failed_free_io:
	iounmap(keypad->mmio_base);
failed_free_mem:
	release_mem_region(res->start, resource_size(res));
failed_free:
	kfree(keypad);
	return err;
}