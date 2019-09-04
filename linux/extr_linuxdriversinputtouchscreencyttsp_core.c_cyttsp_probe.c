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
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct device {int dummy; } ;
struct cyttsp_bus_ops {int /*<<< orphan*/  bustype; } ;
struct cyttsp {int irq; struct device* dev; int /*<<< orphan*/  phys; int /*<<< orphan*/  bl_ready; int /*<<< orphan*/  reset_gpio; struct cyttsp_bus_ops const* bus_ops; struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  CY_MAX_ID ; 
 int ENOMEM ; 
 struct cyttsp* ERR_PTR (int) ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyttsp_close ; 
 int /*<<< orphan*/  cyttsp_hard_reset (struct cyttsp*) ; 
 int /*<<< orphan*/  cyttsp_irq ; 
 int /*<<< orphan*/  cyttsp_open ; 
 int cyttsp_parse_properties (struct cyttsp*) ; 
 int cyttsp_power_on (struct cyttsp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct cyttsp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct cyttsp*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct cyttsp*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

struct cyttsp *cyttsp_probe(const struct cyttsp_bus_ops *bus_ops,
			    struct device *dev, int irq, size_t xfer_buf_size)
{
	struct cyttsp *ts;
	struct input_dev *input_dev;
	int error;

	ts = devm_kzalloc(dev, sizeof(*ts) + xfer_buf_size, GFP_KERNEL);
	if (!ts)
		return ERR_PTR(-ENOMEM);

	input_dev = devm_input_allocate_device(dev);
	if (!input_dev)
		return ERR_PTR(-ENOMEM);

	ts->dev = dev;
	ts->input = input_dev;
	ts->bus_ops = bus_ops;
	ts->irq = irq;

	ts->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ts->reset_gpio)) {
		error = PTR_ERR(ts->reset_gpio);
		dev_err(dev, "Failed to request reset gpio, error %d\n", error);
		return ERR_PTR(error);
	}

	error = cyttsp_parse_properties(ts);
	if (error)
		return ERR_PTR(error);

	init_completion(&ts->bl_ready);
	snprintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(dev));

	input_dev->name = "Cypress TTSP TouchScreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = bus_ops->bustype;
	input_dev->dev.parent = ts->dev;

	input_dev->open = cyttsp_open;
	input_dev->close = cyttsp_close;

	input_set_drvdata(input_dev, ts);

	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	touchscreen_parse_properties(input_dev, true, NULL);

	error = input_mt_init_slots(input_dev, CY_MAX_ID, 0);
	if (error) {
		dev_err(dev, "Unable to init MT slots.\n");
		return ERR_PTR(error);
	}

	error = devm_request_threaded_irq(dev, ts->irq, NULL, cyttsp_irq,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  "cyttsp", ts);
	if (error) {
		dev_err(ts->dev, "failed to request IRQ %d, err: %d\n",
			ts->irq, error);
		return ERR_PTR(error);
	}

	disable_irq(ts->irq);

	cyttsp_hard_reset(ts);

	error = cyttsp_power_on(ts);
	if (error)
		return ERR_PTR(error);

	error = input_register_device(input_dev);
	if (error) {
		dev_err(ts->dev, "failed to register input device: %d\n",
			error);
		return ERR_PTR(error);
	}

	return ts;
}