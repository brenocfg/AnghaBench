#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct meson_i2c_data {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; TYPE_2__* parent; } ;
struct TYPE_12__ {struct meson_i2c* algo_data; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct meson_i2c {int /*<<< orphan*/  clk; TYPE_4__ adap; int /*<<< orphan*/  regs; struct meson_i2c_data const* data; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; TYPE_2__* dev; } ;
struct i2c_timings {int /*<<< orphan*/  bus_freq_hz; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  REG_CTRL_START ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct meson_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct meson_i2c*) ; 
 int i2c_add_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_parse_fw_timings (TYPE_2__*,struct i2c_timings*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meson_i2c_algorithm ; 
 int /*<<< orphan*/  meson_i2c_irq ; 
 int /*<<< orphan*/  meson_i2c_set_clk_div (struct meson_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_i2c_set_mask (struct meson_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (TYPE_2__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_i2c*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int meson_i2c_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct meson_i2c *i2c;
	struct resource *mem;
	struct i2c_timings timings;
	int irq, ret = 0;

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct meson_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c_parse_fw_timings(&pdev->dev, &timings, true);

	i2c->dev = &pdev->dev;
	platform_set_drvdata(pdev, i2c);

	spin_lock_init(&i2c->lock);
	init_completion(&i2c->done);

	i2c->data = (const struct meson_i2c_data *)
		of_device_get_match_data(&pdev->dev);

	i2c->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "can't get device clock\n");
		return PTR_ERR(i2c->clk);
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(i2c->regs))
		return PTR_ERR(i2c->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "can't find IRQ\n");
		return irq;
	}

	ret = devm_request_irq(&pdev->dev, irq, meson_i2c_irq, 0, NULL, i2c);
	if (ret < 0) {
		dev_err(&pdev->dev, "can't request IRQ\n");
		return ret;
	}

	ret = clk_prepare(i2c->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "can't prepare clock\n");
		return ret;
	}

	strlcpy(i2c->adap.name, "Meson I2C adapter",
		sizeof(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &meson_i2c_algorithm;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;

	/*
	 * A transfer is triggered when START bit changes from 0 to 1.
	 * Ensure that the bit is set to 0 after probe
	 */
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_START, 0);

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0) {
		clk_unprepare(i2c->clk);
		return ret;
	}

	meson_i2c_set_clk_div(i2c, timings.bus_freq_hz);

	return 0;
}