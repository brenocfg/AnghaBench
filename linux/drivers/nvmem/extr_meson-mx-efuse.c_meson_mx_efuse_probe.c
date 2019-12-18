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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct meson_mx_efuse_platform_data {int /*<<< orphan*/  word_size; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int read_only; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; int /*<<< orphan*/  word_size; int /*<<< orphan*/  stride; struct meson_mx_efuse* priv; int /*<<< orphan*/ * dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct meson_mx_efuse {int /*<<< orphan*/  nvmem; TYPE_1__ config; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_512 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  devm_kstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_mx_efuse* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_nvmem_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  meson_mx_efuse_read ; 
 struct meson_mx_efuse_platform_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_mx_efuse_probe(struct platform_device *pdev)
{
	const struct meson_mx_efuse_platform_data *drvdata;
	struct meson_mx_efuse *efuse;
	struct resource *res;

	drvdata = of_device_get_match_data(&pdev->dev);
	if (!drvdata)
		return -EINVAL;

	efuse = devm_kzalloc(&pdev->dev, sizeof(*efuse), GFP_KERNEL);
	if (!efuse)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	efuse->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(efuse->base))
		return PTR_ERR(efuse->base);

	efuse->config.name = devm_kstrdup(&pdev->dev, drvdata->name,
					  GFP_KERNEL);
	efuse->config.owner = THIS_MODULE;
	efuse->config.dev = &pdev->dev;
	efuse->config.priv = efuse;
	efuse->config.stride = drvdata->word_size;
	efuse->config.word_size = drvdata->word_size;
	efuse->config.size = SZ_512;
	efuse->config.read_only = true;
	efuse->config.reg_read = meson_mx_efuse_read;

	efuse->core_clk = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(efuse->core_clk)) {
		dev_err(&pdev->dev, "Failed to get core clock\n");
		return PTR_ERR(efuse->core_clk);
	}

	efuse->nvmem = devm_nvmem_register(&pdev->dev, &efuse->config);

	return PTR_ERR_OR_ZERO(efuse->nvmem);
}