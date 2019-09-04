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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct exynos_rng_dev {int type; int /*<<< orphan*/  mem; int /*<<< orphan*/  clk; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; } ;
typedef  enum exynos_prng_type { ____Placeholder_exynos_prng_type } exynos_prng_type ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int crypto_register_rng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct exynos_rng_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_rng_alg ; 
 struct exynos_rng_dev* exynos_rng_dev ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_rng_dev*) ; 

__attribute__((used)) static int exynos_rng_probe(struct platform_device *pdev)
{
	struct exynos_rng_dev *rng;
	struct resource *res;
	int ret;

	if (exynos_rng_dev)
		return -EEXIST;

	rng = devm_kzalloc(&pdev->dev, sizeof(*rng), GFP_KERNEL);
	if (!rng)
		return -ENOMEM;

	rng->type = (enum exynos_prng_type)of_device_get_match_data(&pdev->dev);

	mutex_init(&rng->lock);

	rng->dev = &pdev->dev;
	rng->clk = devm_clk_get(&pdev->dev, "secss");
	if (IS_ERR(rng->clk)) {
		dev_err(&pdev->dev, "Couldn't get clock.\n");
		return PTR_ERR(rng->clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rng->mem = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rng->mem))
		return PTR_ERR(rng->mem);

	platform_set_drvdata(pdev, rng);

	exynos_rng_dev = rng;

	ret = crypto_register_rng(&exynos_rng_alg);
	if (ret) {
		dev_err(&pdev->dev,
			"Couldn't register rng crypto alg: %d\n", ret);
		exynos_rng_dev = NULL;
	}

	return ret;
}