#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {struct device_node* of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int timeout; TYPE_1__ dev; int /*<<< orphan*/ * algo; scalar_t__ retries; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct stm32f4_i2c_dev {struct reset_control* clk; TYPE_2__* dev; int /*<<< orphan*/  complete; struct i2c_adapter adap; int /*<<< orphan*/  speed; struct reset_control* base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct reset_control {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  STM32_I2C_SPEED_FAST ; 
 int /*<<< orphan*/  STM32_I2C_SPEED_STANDARD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable (struct reset_control*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct reset_control*) ; 
 int clk_prepare_enable (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct reset_control* devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct reset_control* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct stm32f4_i2c_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32f4_i2c_dev*) ; 
 struct reset_control* devm_reset_control_get_exclusive (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int irq_of_parse_and_map (struct device_node*,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32f4_i2c_algo ; 
 int stm32f4_i2c_hw_config (struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  stm32f4_i2c_isr_error ; 
 int /*<<< orphan*/  stm32f4_i2c_isr_event ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32f4_i2c_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct stm32f4_i2c_dev *i2c_dev;
	struct resource *res;
	u32 irq_event, irq_error, clk_rate;
	struct i2c_adapter *adap;
	struct reset_control *rst;
	int ret;

	i2c_dev = devm_kzalloc(&pdev->dev, sizeof(*i2c_dev), GFP_KERNEL);
	if (!i2c_dev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c_dev->base))
		return PTR_ERR(i2c_dev->base);

	irq_event = irq_of_parse_and_map(np, 0);
	if (!irq_event) {
		dev_err(&pdev->dev, "IRQ event missing or invalid\n");
		return -EINVAL;
	}

	irq_error = irq_of_parse_and_map(np, 1);
	if (!irq_error) {
		dev_err(&pdev->dev, "IRQ error missing or invalid\n");
		return -EINVAL;
	}

	i2c_dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c_dev->clk)) {
		dev_err(&pdev->dev, "Error: Missing controller clock\n");
		return PTR_ERR(i2c_dev->clk);
	}
	ret = clk_prepare_enable(i2c_dev->clk);
	if (ret) {
		dev_err(i2c_dev->dev, "Failed to prepare_enable clock\n");
		return ret;
	}

	rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(rst)) {
		dev_err(&pdev->dev, "Error: Missing controller reset\n");
		ret = PTR_ERR(rst);
		goto clk_free;
	}
	reset_control_assert(rst);
	udelay(2);
	reset_control_deassert(rst);

	i2c_dev->speed = STM32_I2C_SPEED_STANDARD;
	ret = of_property_read_u32(np, "clock-frequency", &clk_rate);
	if (!ret && clk_rate >= 400000)
		i2c_dev->speed = STM32_I2C_SPEED_FAST;

	i2c_dev->dev = &pdev->dev;

	ret = devm_request_irq(&pdev->dev, irq_event, stm32f4_i2c_isr_event, 0,
			       pdev->name, i2c_dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq event %i\n",
			irq_event);
		goto clk_free;
	}

	ret = devm_request_irq(&pdev->dev, irq_error, stm32f4_i2c_isr_error, 0,
			       pdev->name, i2c_dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq error %i\n",
			irq_error);
		goto clk_free;
	}

	ret = stm32f4_i2c_hw_config(i2c_dev);
	if (ret)
		goto clk_free;

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snprintf(adap->name, sizeof(adap->name), "STM32 I2C(%pa)", &res->start);
	adap->owner = THIS_MODULE;
	adap->timeout = 2 * HZ;
	adap->retries = 0;
	adap->algo = &stm32f4_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&i2c_dev->complete);

	ret = i2c_add_adapter(adap);
	if (ret)
		goto clk_free;

	platform_set_drvdata(pdev, i2c_dev);

	clk_disable(i2c_dev->clk);

	dev_info(i2c_dev->dev, "STM32F4 I2C driver registered\n");

	return 0;

clk_free:
	clk_disable_unprepare(i2c_dev->clk);
	return ret;
}