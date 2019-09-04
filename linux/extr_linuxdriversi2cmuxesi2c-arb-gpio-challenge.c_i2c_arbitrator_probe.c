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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct i2c_mux_core {int /*<<< orphan*/  parent; } ;
struct i2c_arbitrator_data {int our_gpio; int our_gpio_release; int their_gpio; int their_gpio_release; int slew_delay_us; int wait_retry_us; int wait_free_us; } ;
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 unsigned long GPIOF_IN ; 
 unsigned long GPIOF_OUT_INIT_HIGH ; 
 unsigned long GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  I2C_MUX_ARBITRATOR ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_get_platdata (struct device*) ; 
 int devm_gpio_request_one (struct device*,int,unsigned long,char*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  i2c_arbitrator_deselect ; 
 int /*<<< orphan*/  i2c_arbitrator_select ; 
 int i2c_mux_add_adapter (struct i2c_mux_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* i2c_mux_alloc (int /*<<< orphan*/ *,struct device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_arbitrator_data* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_i2c_adapter_by_node (struct device_node*) ; 
 int of_get_named_gpio (struct device_node*,char*,int) ; 
 int of_get_named_gpio_flags (struct device_node*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_mux_core*) ; 

__attribute__((used)) static int i2c_arbitrator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct device_node *parent_np;
	struct i2c_mux_core *muxc;
	struct i2c_arbitrator_data *arb;
	enum of_gpio_flags gpio_flags;
	unsigned long out_init;
	int ret;

	/* We only support probing from device tree; no platform_data */
	if (!np) {
		dev_err(dev, "Cannot find device tree node\n");
		return -ENODEV;
	}
	if (dev_get_platdata(dev)) {
		dev_err(dev, "Platform data is not supported\n");
		return -EINVAL;
	}

	muxc = i2c_mux_alloc(NULL, dev, 1, sizeof(*arb), I2C_MUX_ARBITRATOR,
			     i2c_arbitrator_select, i2c_arbitrator_deselect);
	if (!muxc)
		return -ENOMEM;
	arb = i2c_mux_priv(muxc);

	platform_set_drvdata(pdev, muxc);

	/* Request GPIOs */
	ret = of_get_named_gpio_flags(np, "our-claim-gpio", 0, &gpio_flags);
	if (!gpio_is_valid(ret)) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Error getting our-claim-gpio\n");
		return ret;
	}
	arb->our_gpio = ret;
	arb->our_gpio_release = !!(gpio_flags & OF_GPIO_ACTIVE_LOW);
	out_init = (gpio_flags & OF_GPIO_ACTIVE_LOW) ?
		GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
	ret = devm_gpio_request_one(dev, arb->our_gpio, out_init,
				    "our-claim-gpio");
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Error requesting our-claim-gpio\n");
		return ret;
	}

	ret = of_get_named_gpio_flags(np, "their-claim-gpios", 0, &gpio_flags);
	if (!gpio_is_valid(ret)) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Error getting their-claim-gpio\n");
		return ret;
	}
	arb->their_gpio = ret;
	arb->their_gpio_release = !!(gpio_flags & OF_GPIO_ACTIVE_LOW);
	ret = devm_gpio_request_one(dev, arb->their_gpio, GPIOF_IN,
				    "their-claim-gpio");
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Error requesting their-claim-gpio\n");
		return ret;
	}

	/* At the moment we only support a single two master (us + 1 other) */
	if (gpio_is_valid(of_get_named_gpio(np, "their-claim-gpios", 1))) {
		dev_err(dev, "Only one other master is supported\n");
		return -EINVAL;
	}

	/* Arbitration parameters */
	if (of_property_read_u32(np, "slew-delay-us", &arb->slew_delay_us))
		arb->slew_delay_us = 10;
	if (of_property_read_u32(np, "wait-retry-us", &arb->wait_retry_us))
		arb->wait_retry_us = 3000;
	if (of_property_read_u32(np, "wait-free-us", &arb->wait_free_us))
		arb->wait_free_us = 50000;

	/* Find our parent */
	parent_np = of_parse_phandle(np, "i2c-parent", 0);
	if (!parent_np) {
		dev_err(dev, "Cannot parse i2c-parent\n");
		return -EINVAL;
	}
	muxc->parent = of_get_i2c_adapter_by_node(parent_np);
	of_node_put(parent_np);
	if (!muxc->parent) {
		dev_err(dev, "Cannot find parent bus\n");
		return -EPROBE_DEFER;
	}

	/* Actually add the mux adapter */
	ret = i2c_mux_add_adapter(muxc, 0, 0, 0);
	if (ret)
		i2c_put_adapter(muxc->parent);

	return ret;
}