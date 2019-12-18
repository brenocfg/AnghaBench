#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ti_iodelay_reg_data {scalar_t__ reg_nr_per_pin; } ;
struct ti_iodelay_device {int /*<<< orphan*/  dev; struct pinctrl_pin_desc* pa; struct ti_iodelay_reg_data* reg_data; } ;
struct ti_iodelay_cfg {int offset; int a_delay; int g_delay; } ;
struct pinctrl_pin_desc {struct ti_iodelay_cfg* drv_data; } ;
struct pinctrl_dev {int dummy; } ;
struct of_phandle_args {scalar_t__ args_count; int* args; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct device_node*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 struct ti_iodelay_device* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int ti_iodelay_offset_to_pin (struct ti_iodelay_device*,int) ; 

__attribute__((used)) static int ti_iodelay_node_iterator(struct pinctrl_dev *pctldev,
				    struct device_node *np,
				    const struct of_phandle_args *pinctrl_spec,
				    int *pins, int pin_index, void *data)
{
	struct ti_iodelay_device *iod;
	struct ti_iodelay_cfg *cfg = data;
	const struct ti_iodelay_reg_data *r;
	struct pinctrl_pin_desc *pd;
	int pin;

	iod = pinctrl_dev_get_drvdata(pctldev);
	if (!iod)
		return -EINVAL;

	r = iod->reg_data;

	if (pinctrl_spec->args_count < r->reg_nr_per_pin) {
		dev_err(iod->dev, "invalid args_count for spec: %i\n",
			pinctrl_spec->args_count);

		return -EINVAL;
	}

	/* Index plus two value cells */
	cfg[pin_index].offset = pinctrl_spec->args[0];
	cfg[pin_index].a_delay = pinctrl_spec->args[1] & 0xffff;
	cfg[pin_index].g_delay = pinctrl_spec->args[2] & 0xffff;

	pin = ti_iodelay_offset_to_pin(iod, cfg[pin_index].offset);
	if (pin < 0) {
		dev_err(iod->dev, "could not add functions for %pOFn %ux\n",
			np, cfg[pin_index].offset);
		return -ENODEV;
	}
	pins[pin_index] = pin;

	pd = &iod->pa[pin];
	pd->drv_data = &cfg[pin_index];

	dev_dbg(iod->dev, "%pOFn offset=%x a_delay = %d g_delay = %d\n",
		np, cfg[pin_index].offset, cfg[pin_index].a_delay,
		cfg[pin_index].g_delay);

	return 0;
}