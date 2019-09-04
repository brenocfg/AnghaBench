#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_4__ {struct device_node* of_node; struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;
struct p2wi {int slave_addr; scalar_t__ clk; scalar_t__ rstc; TYPE_2__ adapter; scalar_t__ regs; int /*<<< orphan*/  complete; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ P2WI_CCR ; 
 int P2WI_CCR_CLK_DIV (int) ; 
 int P2WI_CCR_MAX_CLK_DIV ; 
 int P2WI_CCR_SDA_OUT_DELAY (int) ; 
 scalar_t__ P2WI_CTRL ; 
 int P2WI_CTRL_SOFT_RST ; 
 unsigned long P2WI_MAX_FREQ ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned long) ; 
 scalar_t__ devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct p2wi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct p2wi*) ; 
 scalar_t__ devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct p2wi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_get_child_count (struct device_node*) ; 
 struct device_node* of_get_next_available_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned long*) ; 
 int /*<<< orphan*/  p2wi_algo ; 
 int /*<<< orphan*/  p2wi_interrupt ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct p2wi*) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 int reset_control_deassert (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int p2wi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct device_node *childnp;
	unsigned long parent_clk_freq;
	u32 clk_freq = 100000;
	struct resource *r;
	struct p2wi *p2wi;
	u32 slave_addr;
	int clk_div;
	int irq;
	int ret;

	of_property_read_u32(np, "clock-frequency", &clk_freq);
	if (clk_freq > P2WI_MAX_FREQ) {
		dev_err(dev,
			"required clock-frequency (%u Hz) is too high (max = 6MHz)",
			clk_freq);
		return -EINVAL;
	}

	if (of_get_child_count(np) > 1) {
		dev_err(dev, "P2WI only supports one slave device\n");
		return -EINVAL;
	}

	p2wi = devm_kzalloc(dev, sizeof(struct p2wi), GFP_KERNEL);
	if (!p2wi)
		return -ENOMEM;

	p2wi->slave_addr = -1;

	/*
	 * Authorize a p2wi node without any children to be able to use an
	 * i2c-dev from userpace.
	 * In this case the slave_addr is set to -1 and won't be checked when
	 * launching a P2WI transfer.
	 */
	childnp = of_get_next_available_child(np, NULL);
	if (childnp) {
		ret = of_property_read_u32(childnp, "reg", &slave_addr);
		if (ret) {
			dev_err(dev, "invalid slave address on node %pOF\n",
				childnp);
			return -EINVAL;
		}

		p2wi->slave_addr = slave_addr;
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	p2wi->regs = devm_ioremap_resource(dev, r);
	if (IS_ERR(p2wi->regs))
		return PTR_ERR(p2wi->regs);

	strlcpy(p2wi->adapter.name, pdev->name, sizeof(p2wi->adapter.name));
	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "failed to retrieve irq: %d\n", irq);
		return irq;
	}

	p2wi->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(p2wi->clk)) {
		ret = PTR_ERR(p2wi->clk);
		dev_err(dev, "failed to retrieve clk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(p2wi->clk);
	if (ret) {
		dev_err(dev, "failed to enable clk: %d\n", ret);
		return ret;
	}

	parent_clk_freq = clk_get_rate(p2wi->clk);

	p2wi->rstc = devm_reset_control_get_exclusive(dev, NULL);
	if (IS_ERR(p2wi->rstc)) {
		ret = PTR_ERR(p2wi->rstc);
		dev_err(dev, "failed to retrieve reset controller: %d\n", ret);
		goto err_clk_disable;
	}

	ret = reset_control_deassert(p2wi->rstc);
	if (ret) {
		dev_err(dev, "failed to deassert reset line: %d\n", ret);
		goto err_clk_disable;
	}

	init_completion(&p2wi->complete);
	p2wi->adapter.dev.parent = dev;
	p2wi->adapter.algo = &p2wi_algo;
	p2wi->adapter.owner = THIS_MODULE;
	p2wi->adapter.dev.of_node = pdev->dev.of_node;
	platform_set_drvdata(pdev, p2wi);
	i2c_set_adapdata(&p2wi->adapter, p2wi);

	ret = devm_request_irq(dev, irq, p2wi_interrupt, 0, pdev->name, p2wi);
	if (ret) {
		dev_err(dev, "can't register interrupt handler irq%d: %d\n",
			irq, ret);
		goto err_reset_assert;
	}

	writel(P2WI_CTRL_SOFT_RST, p2wi->regs + P2WI_CTRL);

	clk_div = parent_clk_freq / clk_freq;
	if (!clk_div) {
		dev_warn(dev,
			 "clock-frequency is too high, setting it to %lu Hz\n",
			 parent_clk_freq);
		clk_div = 1;
	} else if (clk_div > P2WI_CCR_MAX_CLK_DIV) {
		dev_warn(dev,
			 "clock-frequency is too low, setting it to %lu Hz\n",
			 parent_clk_freq / P2WI_CCR_MAX_CLK_DIV);
		clk_div = P2WI_CCR_MAX_CLK_DIV;
	}

	writel(P2WI_CCR_SDA_OUT_DELAY(1) | P2WI_CCR_CLK_DIV(clk_div),
	       p2wi->regs + P2WI_CCR);

	ret = i2c_add_adapter(&p2wi->adapter);
	if (!ret)
		return 0;

err_reset_assert:
	reset_control_assert(p2wi->rstc);

err_clk_disable:
	clk_disable_unprepare(p2wi->clk);

	return ret;
}