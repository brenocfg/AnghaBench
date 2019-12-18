#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {char* name; TYPE_3__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; TYPE_3__* parent; } ;
struct TYPE_11__ {int retries; int /*<<< orphan*/  name; TYPE_1__ dev; struct jz4780_i2c* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct jz4780_i2c {unsigned int speed; int /*<<< orphan*/  clk; TYPE_2__ adap; int /*<<< orphan*/  irq; int /*<<< orphan*/  iomem; int /*<<< orphan*/  lock; int /*<<< orphan*/  trans_waitq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ4780_I2C_CTRL ; 
 unsigned short JZ4780_I2C_CTRL_STPHLD ; 
 int /*<<< orphan*/  JZ4780_I2C_INTM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct jz4780_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4780_i2c*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4780_i2c_algorithm ; 
 int /*<<< orphan*/  jz4780_i2c_irq ; 
 unsigned short jz4780_i2c_readw (struct jz4780_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_i2c_set_speed (struct jz4780_i2c*) ; 
 int /*<<< orphan*/  jz4780_i2c_writew (struct jz4780_i2c*,int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4780_i2c*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int jz4780_i2c_probe(struct platform_device *pdev)
{
	int ret = 0;
	unsigned int clk_freq = 0;
	unsigned short tmp;
	struct resource *r;
	struct jz4780_i2c *i2c;

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct jz4780_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->adap.owner		= THIS_MODULE;
	i2c->adap.algo		= &jz4780_i2c_algorithm;
	i2c->adap.algo_data	= i2c;
	i2c->adap.retries	= 5;
	i2c->adap.dev.parent	= &pdev->dev;
	i2c->adap.dev.of_node	= pdev->dev.of_node;
	sprintf(i2c->adap.name, "%s", pdev->name);

	init_completion(&i2c->trans_waitq);
	spin_lock_init(&i2c->lock);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->iomem = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(i2c->iomem))
		return PTR_ERR(i2c->iomem);

	platform_set_drvdata(pdev, i2c);

	i2c->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c->clk))
		return PTR_ERR(i2c->clk);

	ret = clk_prepare_enable(i2c->clk);
	if (ret)
		return ret;

	ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				   &clk_freq);
	if (ret) {
		dev_err(&pdev->dev, "clock-frequency not specified in DT\n");
		goto err;
	}

	i2c->speed = clk_freq / 1000;
	if (i2c->speed == 0) {
		ret = -EINVAL;
		dev_err(&pdev->dev, "clock-frequency minimum is 1000\n");
		goto err;
	}
	jz4780_i2c_set_speed(i2c);

	dev_info(&pdev->dev, "Bus frequency is %d KHz\n", i2c->speed);

	tmp = jz4780_i2c_readw(i2c, JZ4780_I2C_CTRL);
	tmp &= ~JZ4780_I2C_CTRL_STPHLD;
	jz4780_i2c_writew(i2c, JZ4780_I2C_CTRL, tmp);

	jz4780_i2c_writew(i2c, JZ4780_I2C_INTM, 0x0);

	i2c->irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, i2c->irq, jz4780_i2c_irq, 0,
			       dev_name(&pdev->dev), i2c);
	if (ret)
		goto err;

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0)
		goto err;

	return 0;

err:
	clk_disable_unprepare(i2c->clk);
	return ret;
}