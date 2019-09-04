#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct pic32_rng {scalar_t__ clk; TYPE_1__ rng; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ RNGCON ; 
 int TRNGEN ; 
 int TRNGMOD ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pic32_rng* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hwrng_register (TYPE_1__*) ; 
 int /*<<< orphan*/  pic32_rng_read ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pic32_rng*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pic32_rng_probe(struct platform_device *pdev)
{
	struct pic32_rng *priv;
	struct resource *res;
	u32 v;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	/* enable TRNG in enhanced mode */
	v = TRNGEN | TRNGMOD;
	writel(v, priv->base + RNGCON);

	priv->rng.name = pdev->name;
	priv->rng.read = pic32_rng_read;

	ret = hwrng_register(&priv->rng);
	if (ret)
		goto err_register;

	platform_set_drvdata(pdev, priv);

	return 0;

err_register:
	clk_disable_unprepare(priv->clk);
	return ret;
}