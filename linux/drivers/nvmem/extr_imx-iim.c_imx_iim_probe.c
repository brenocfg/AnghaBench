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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {struct imx_iim_drvdata* data; } ;
struct nvmem_device {int dummy; } ;
struct nvmem_config {char* name; int read_only; int word_size; int stride; struct iim_priv* priv; int /*<<< orphan*/  size; struct device* dev; int /*<<< orphan*/  reg_read; } ;
struct imx_iim_drvdata {int /*<<< orphan*/  nregs; } ;
struct iim_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct nvmem_device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct iim_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (struct device*,struct nvmem_config*) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_iim_dt_ids ; 
 int /*<<< orphan*/  imx_iim_read ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int imx_iim_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id;
	struct device *dev = &pdev->dev;
	struct iim_priv *iim;
	struct nvmem_device *nvmem;
	struct nvmem_config cfg = {};
	const struct imx_iim_drvdata *drvdata = NULL;

	iim = devm_kzalloc(dev, sizeof(*iim), GFP_KERNEL);
	if (!iim)
		return -ENOMEM;

	iim->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(iim->base))
		return PTR_ERR(iim->base);

	of_id = of_match_device(imx_iim_dt_ids, dev);
	if (!of_id)
		return -ENODEV;

	drvdata = of_id->data;

	iim->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(iim->clk))
		return PTR_ERR(iim->clk);

	cfg.name = "imx-iim",
	cfg.read_only = true,
	cfg.word_size = 1,
	cfg.stride = 1,
	cfg.reg_read = imx_iim_read,
	cfg.dev = dev;
	cfg.size = drvdata->nregs;
	cfg.priv = iim;

	nvmem = devm_nvmem_register(dev, &cfg);

	return PTR_ERR_OR_ZERO(nvmem);
}