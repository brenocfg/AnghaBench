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
struct i2c_arbitrator_data {int slew_delay_us; int wait_retry_us; int wait_free_us; struct gpio_desc* their_gpio; struct gpio_desc* our_gpio; } ;
struct gpio_desc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_MUX_ARBITRATOR ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ dev_get_platdata (struct device*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_arbitrator_deselect ; 
 int /*<<< orphan*/  i2c_arbitrator_select ; 
 int i2c_mux_add_adapter (struct i2c_mux_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* i2c_mux_alloc (int /*<<< orphan*/ *,struct device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_arbitrator_data* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_i2c_adapter_by_node (struct device_node*) ; 
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
	struct gpio_desc *dummy;
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

	/* Request GPIOs, our GPIO as unclaimed to begin with */
	arb->our_gpio = devm_gpiod_get(dev, "our-claim", GPIOD_OUT_LOW);
	if (IS_ERR(arb->our_gpio)) {
		dev_err(dev, "could not get \"our-claim\" GPIO (%ld)\n",
			PTR_ERR(arb->our_gpio));
		return PTR_ERR(arb->our_gpio);
	}

	arb->their_gpio = devm_gpiod_get(dev, "their-claim", GPIOD_IN);
	if (IS_ERR(arb->their_gpio)) {
		dev_err(dev, "could not get \"their-claim\" GPIO (%ld)\n",
			PTR_ERR(arb->their_gpio));
		return PTR_ERR(arb->their_gpio);
	}

	/* At the moment we only support a single two master (us + 1 other) */
	dummy = devm_gpiod_get_index(dev, "their-claim", 1, GPIOD_IN);
	if (!IS_ERR(dummy)) {
		dev_err(dev, "Only one other master is supported\n");
		return -EINVAL;
	} else if (PTR_ERR(dummy) == -EPROBE_DEFER) {
		return -EPROBE_DEFER;
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