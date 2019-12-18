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
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_5__ {TYPE_3__* parent; } ;
struct TYPE_4__ {int version; int vendor; int product; } ;
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; } ;
struct da9052_tsi {int stopped; struct da9052* da9052; struct input_dev* dev; int /*<<< orphan*/  ts_pen_work; } ;
struct da9052 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  DA9052_IRQ_PENDOWN ; 
 int /*<<< orphan*/  DA9052_IRQ_TSIREADY ; 
 int /*<<< orphan*/  DA9052_TSI_CONT_A_REG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da9052_configure_tsi (struct da9052_tsi*) ; 
 int /*<<< orphan*/  da9052_disable_irq (struct da9052*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_free_irq (struct da9052*,int /*<<< orphan*/ ,struct da9052_tsi*) ; 
 int /*<<< orphan*/  da9052_reg_update (struct da9052*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int da9052_request_irq (struct da9052*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct da9052_tsi*) ; 
 int /*<<< orphan*/  da9052_ts_adc_toggle (struct da9052_tsi*,int) ; 
 int /*<<< orphan*/  da9052_ts_datardy_irq ; 
 int /*<<< orphan*/  da9052_ts_input_close ; 
 int /*<<< orphan*/  da9052_ts_input_open ; 
 int /*<<< orphan*/  da9052_ts_pen_work ; 
 int /*<<< orphan*/  da9052_ts_pendwn_irq ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9052* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct da9052_tsi*) ; 
 int /*<<< orphan*/  kfree (struct da9052_tsi*) ; 
 struct da9052_tsi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9052_tsi*) ; 

__attribute__((used)) static int da9052_ts_probe(struct platform_device *pdev)
{
	struct da9052 *da9052;
	struct da9052_tsi *tsi;
	struct input_dev *input_dev;
	int error;

	da9052 = dev_get_drvdata(pdev->dev.parent);
	if (!da9052)
		return -EINVAL;

	tsi = kzalloc(sizeof(struct da9052_tsi), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!tsi || !input_dev) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	tsi->da9052 = da9052;
	tsi->dev = input_dev;
	tsi->stopped = true;
	INIT_DELAYED_WORK(&tsi->ts_pen_work, da9052_ts_pen_work);

	input_dev->id.version = 0x0101;
	input_dev->id.vendor = 0x15B6;
	input_dev->id.product = 0x9052;
	input_dev->name = "Dialog DA9052 TouchScreen Driver";
	input_dev->dev.parent = &pdev->dev;
	input_dev->open = da9052_ts_input_open;
	input_dev->close = da9052_ts_input_close;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_abs_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 1023, 0, 0);

	input_set_drvdata(input_dev, tsi);

	/* Disable Pen Detect Circuit */
	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 1, 0);

	/* Disable ADC */
	da9052_ts_adc_toggle(tsi, false);

	error = da9052_request_irq(tsi->da9052, DA9052_IRQ_PENDOWN,
				"pendown-irq", da9052_ts_pendwn_irq, tsi);
	if (error) {
		dev_err(tsi->da9052->dev,
			"Failed to register PENDWN IRQ: %d\n", error);
		goto err_free_mem;
	}

	error = da9052_request_irq(tsi->da9052, DA9052_IRQ_TSIREADY,
				"tsiready-irq", da9052_ts_datardy_irq, tsi);
	if (error) {
		dev_err(tsi->da9052->dev,
			"Failed to register TSIRDY IRQ :%d\n", error);
		goto err_free_pendwn_irq;
	}

	/* Mask PEN_DOWN and TSI_READY events */
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);

	error = da9052_configure_tsi(tsi);
	if (error)
		goto err_free_datardy_irq;

	error = input_register_device(tsi->dev);
	if (error)
		goto err_free_datardy_irq;

	platform_set_drvdata(pdev, tsi);

	return 0;

err_free_datardy_irq:
	da9052_free_irq(tsi->da9052, DA9052_IRQ_TSIREADY, tsi);
err_free_pendwn_irq:
	da9052_free_irq(tsi->da9052, DA9052_IRQ_PENDOWN, tsi);
err_free_mem:
	kfree(tsi);
	input_free_device(input_dev);

	return error;
}