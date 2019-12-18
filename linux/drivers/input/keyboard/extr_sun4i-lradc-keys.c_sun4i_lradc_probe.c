#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sun4i_lradc_data {int chan0_map_count; TYPE_3__* input; int /*<<< orphan*/  base; TYPE_2__* chan0_map; struct device* dev; int /*<<< orphan*/  vref_supply; int /*<<< orphan*/  variant; } ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_6__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_8__ {char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 TYPE_3__* devm_input_allocate_device (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,int /*<<< orphan*/ ) ; 
 struct sun4i_lradc_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sun4i_lradc_data*) ; 
 int input_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_3__*,struct sun4i_lradc_data*) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_lradc_close ; 
 int /*<<< orphan*/  sun4i_lradc_irq ; 
 int sun4i_lradc_load_dt_keymap (struct device*,struct sun4i_lradc_data*) ; 
 int /*<<< orphan*/  sun4i_lradc_open ; 

__attribute__((used)) static int sun4i_lradc_probe(struct platform_device *pdev)
{
	struct sun4i_lradc_data *lradc;
	struct device *dev = &pdev->dev;
	int i;
	int error;

	lradc = devm_kzalloc(dev, sizeof(struct sun4i_lradc_data), GFP_KERNEL);
	if (!lradc)
		return -ENOMEM;

	error = sun4i_lradc_load_dt_keymap(dev, lradc);
	if (error)
		return error;

	lradc->variant = of_device_get_match_data(&pdev->dev);
	if (!lradc->variant) {
		dev_err(&pdev->dev, "Missing sun4i-a10-lradc-keys variant\n");
		return -EINVAL;
	}

	lradc->vref_supply = devm_regulator_get(dev, "vref");
	if (IS_ERR(lradc->vref_supply))
		return PTR_ERR(lradc->vref_supply);

	lradc->dev = dev;
	lradc->input = devm_input_allocate_device(dev);
	if (!lradc->input)
		return -ENOMEM;

	lradc->input->name = pdev->name;
	lradc->input->phys = "sun4i_lradc/input0";
	lradc->input->open = sun4i_lradc_open;
	lradc->input->close = sun4i_lradc_close;
	lradc->input->id.bustype = BUS_HOST;
	lradc->input->id.vendor = 0x0001;
	lradc->input->id.product = 0x0001;
	lradc->input->id.version = 0x0100;

	__set_bit(EV_KEY, lradc->input->evbit);
	for (i = 0; i < lradc->chan0_map_count; i++)
		__set_bit(lradc->chan0_map[i].keycode, lradc->input->keybit);

	input_set_drvdata(lradc->input, lradc);

	lradc->base = devm_ioremap_resource(dev,
			      platform_get_resource(pdev, IORESOURCE_MEM, 0));
	if (IS_ERR(lradc->base))
		return PTR_ERR(lradc->base);

	error = devm_request_irq(dev, platform_get_irq(pdev, 0),
				 sun4i_lradc_irq, 0,
				 "sun4i-a10-lradc-keys", lradc);
	if (error)
		return error;

	error = input_register_device(lradc->input);
	if (error)
		return error;

	return 0;
}