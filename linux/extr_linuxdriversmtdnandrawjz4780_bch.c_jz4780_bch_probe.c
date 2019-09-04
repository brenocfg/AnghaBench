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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct jz4780_bch {struct device* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCH_CLK_RATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct jz4780_bch* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_bch_disable (struct jz4780_bch*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4780_bch*) ; 

__attribute__((used)) static int jz4780_bch_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct jz4780_bch *bch;
	struct resource *res;

	bch = devm_kzalloc(dev, sizeof(*bch), GFP_KERNEL);
	if (!bch)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	bch->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(bch->base))
		return PTR_ERR(bch->base);

	jz4780_bch_disable(bch);

	bch->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(bch->clk)) {
		dev_err(dev, "failed to get clock: %ld\n", PTR_ERR(bch->clk));
		return PTR_ERR(bch->clk);
	}

	clk_set_rate(bch->clk, BCH_CLK_RATE);

	mutex_init(&bch->lock);

	bch->dev = dev;
	platform_set_drvdata(pdev, bch);

	return 0;
}