#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; int word_size; int stride; int read_only; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; int /*<<< orphan*/  owner; struct stm32_romem_priv* priv; struct device* dev; } ;
struct stm32_romem_priv {TYPE_3__ cfg; int /*<<< orphan*/  base; } ;
struct stm32_romem_cfg {int /*<<< orphan*/  size; } ;
struct resource {int dummy; } ;
struct device {TYPE_1__* driver; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct stm32_romem_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_nvmem_register (struct device*,TYPE_3__*) ; 
 TYPE_2__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  stm32_bsec_read ; 
 int /*<<< orphan*/  stm32_bsec_write ; 
 int /*<<< orphan*/  stm32_romem_read ; 

__attribute__((used)) static int stm32_romem_probe(struct platform_device *pdev)
{
	const struct stm32_romem_cfg *cfg;
	struct device *dev = &pdev->dev;
	struct stm32_romem_priv *priv;
	struct resource *res;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->cfg.name = "stm32-romem";
	priv->cfg.word_size = 1;
	priv->cfg.stride = 1;
	priv->cfg.dev = dev;
	priv->cfg.priv = priv;
	priv->cfg.owner = THIS_MODULE;

	cfg = (const struct stm32_romem_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;
	if (!cfg) {
		priv->cfg.read_only = true;
		priv->cfg.size = resource_size(res);
		priv->cfg.reg_read = stm32_romem_read;
	} else {
		priv->cfg.size = cfg->size;
		priv->cfg.reg_read = stm32_bsec_read;
		priv->cfg.reg_write = stm32_bsec_write;
	}

	return PTR_ERR_OR_ZERO(devm_nvmem_register(dev, &priv->cfg));
}