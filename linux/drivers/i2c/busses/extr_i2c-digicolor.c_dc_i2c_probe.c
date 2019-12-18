#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; TYPE_3__* parent; } ;
struct TYPE_9__ {struct dc_i2c* algo_data; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct dc_i2c {int /*<<< orphan*/  clk; TYPE_2__ adap; int /*<<< orphan*/  regs; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; TYPE_3__* dev; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FREQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_i2c_algorithm ; 
 int dc_i2c_init_hw (struct dc_i2c*) ; 
 int /*<<< orphan*/  dc_i2c_irq ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct dc_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dc_i2c*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dc_i2c*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dc_i2c_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct dc_i2c *i2c;
	struct resource *r;
	int ret = 0, irq;

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct dc_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	if (of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				 &i2c->frequency))
		i2c->frequency = DEFAULT_FREQ;

	i2c->dev = &pdev->dev;
	platform_set_drvdata(pdev, i2c);

	spin_lock_init(&i2c->lock);
	init_completion(&i2c->done);

	i2c->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c->clk))
		return PTR_ERR(i2c->clk);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->regs = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(i2c->regs))
		return PTR_ERR(i2c->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(&pdev->dev, irq, dc_i2c_irq, 0,
			       dev_name(&pdev->dev), i2c);
	if (ret < 0)
		return ret;

	strlcpy(i2c->adap.name, "Conexant Digicolor I2C adapter",
		sizeof(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &dc_i2c_algorithm;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;

	ret = dc_i2c_init_hw(i2c);
	if (ret)
		return ret;

	ret = clk_prepare_enable(i2c->clk);
	if (ret < 0)
		return ret;

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0) {
		clk_disable_unprepare(i2c->clk);
		return ret;
	}

	return 0;
}