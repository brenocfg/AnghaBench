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
struct i2c_adapter {int timeout; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * bus_recovery_info; int /*<<< orphan*/ * algo; scalar_t__ retries; int /*<<< orphan*/  owner; } ;
struct st_i2c_dev {TYPE_2__* dev; int /*<<< orphan*/  complete; struct i2c_adapter adap; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  I2C_MODE_FAST ; 
 int /*<<< orphan*/  I2C_MODE_STANDARD ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct st_i2c_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct st_i2c_dev*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct st_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_get_by_name (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (TYPE_2__*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_idle_state (TYPE_2__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct st_i2c_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_i2c_algo ; 
 int /*<<< orphan*/  st_i2c_isr_thread ; 
 int st_i2c_of_get_deglitch (struct device_node*,struct st_i2c_dev*) ; 
 int /*<<< orphan*/  st_i2c_recovery_info ; 

__attribute__((used)) static int st_i2c_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct st_i2c_dev *i2c_dev;
	struct resource *res;
	u32 clk_rate;
	struct i2c_adapter *adap;
	int ret;

	i2c_dev = devm_kzalloc(&pdev->dev, sizeof(*i2c_dev), GFP_KERNEL);
	if (!i2c_dev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c_dev->base))
		return PTR_ERR(i2c_dev->base);

	i2c_dev->irq = irq_of_parse_and_map(np, 0);
	if (!i2c_dev->irq) {
		dev_err(&pdev->dev, "IRQ missing or invalid\n");
		return -EINVAL;
	}

	i2c_dev->clk = of_clk_get_by_name(np, "ssc");
	if (IS_ERR(i2c_dev->clk)) {
		dev_err(&pdev->dev, "Unable to request clock\n");
		return PTR_ERR(i2c_dev->clk);
	}

	i2c_dev->mode = I2C_MODE_STANDARD;
	ret = of_property_read_u32(np, "clock-frequency", &clk_rate);
	if ((!ret) && (clk_rate == 400000))
		i2c_dev->mode = I2C_MODE_FAST;

	i2c_dev->dev = &pdev->dev;

	ret = devm_request_threaded_irq(&pdev->dev, i2c_dev->irq,
			NULL, st_i2c_isr_thread,
			IRQF_ONESHOT, pdev->name, i2c_dev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq %i\n", i2c_dev->irq);
		return ret;
	}

	pinctrl_pm_select_default_state(i2c_dev->dev);
	/* In case idle state available, select it */
	pinctrl_pm_select_idle_state(i2c_dev->dev);

	ret = st_i2c_of_get_deglitch(np, i2c_dev);
	if (ret)
		return ret;

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snprintf(adap->name, sizeof(adap->name), "ST I2C(%pa)", &res->start);
	adap->owner = THIS_MODULE;
	adap->timeout = 2 * HZ;
	adap->retries = 0;
	adap->algo = &st_i2c_algo;
	adap->bus_recovery_info = &st_i2c_recovery_info;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&i2c_dev->complete);

	ret = i2c_add_adapter(adap);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, i2c_dev);

	dev_info(i2c_dev->dev, "%s initialized\n", adap->name);

	return 0;
}