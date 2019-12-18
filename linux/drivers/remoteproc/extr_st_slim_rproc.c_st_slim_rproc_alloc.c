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
struct st_slim_rproc {scalar_t__* clks; void* peri; void* slimcore; TYPE_1__* mem; struct rproc* rproc; } ;
struct rproc {int has_iommu; struct st_slim_rproc* priv; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bus_addr; void* cpu_addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct st_slim_rproc* ERR_PTR (int) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int ST_SLIM_MAX_CLK ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 char** mem_names ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 
 int /*<<< orphan*/  slim_clk_disable (struct st_slim_rproc*) ; 
 int slim_clk_enable (struct st_slim_rproc*) ; 
 int slim_clk_get (struct st_slim_rproc*,struct device*) ; 
 int /*<<< orphan*/  slim_rproc_ops ; 

struct st_slim_rproc *st_slim_rproc_alloc(struct platform_device *pdev,
				char *fw_name)
{
	struct device *dev = &pdev->dev;
	struct st_slim_rproc *slim_rproc;
	struct device_node *np = dev->of_node;
	struct rproc *rproc;
	struct resource *res;
	int err, i;

	if (!fw_name)
		return ERR_PTR(-EINVAL);

	if (!of_device_is_compatible(np, "st,slim-rproc"))
		return ERR_PTR(-EINVAL);

	rproc = rproc_alloc(dev, np->name, &slim_rproc_ops,
			fw_name, sizeof(*slim_rproc));
	if (!rproc)
		return ERR_PTR(-ENOMEM);

	rproc->has_iommu = false;

	slim_rproc = rproc->priv;
	slim_rproc->rproc = rproc;

	/* get imem and dmem */
	for (i = 0; i < ARRAY_SIZE(mem_names); i++) {
		res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						mem_names[i]);

		slim_rproc->mem[i].cpu_addr = devm_ioremap_resource(dev, res);
		if (IS_ERR(slim_rproc->mem[i].cpu_addr)) {
			dev_err(&pdev->dev, "devm_ioremap_resource failed\n");
			err = PTR_ERR(slim_rproc->mem[i].cpu_addr);
			goto err;
		}
		slim_rproc->mem[i].bus_addr = res->start;
		slim_rproc->mem[i].size = resource_size(res);
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "slimcore");
	slim_rproc->slimcore = devm_ioremap_resource(dev, res);
	if (IS_ERR(slim_rproc->slimcore)) {
		dev_err(&pdev->dev, "failed to ioremap slimcore IO\n");
		err = PTR_ERR(slim_rproc->slimcore);
		goto err;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "peripherals");
	slim_rproc->peri = devm_ioremap_resource(dev, res);
	if (IS_ERR(slim_rproc->peri)) {
		dev_err(&pdev->dev, "failed to ioremap peripherals IO\n");
		err = PTR_ERR(slim_rproc->peri);
		goto err;
	}

	err = slim_clk_get(slim_rproc, dev);
	if (err)
		goto err;

	err = slim_clk_enable(slim_rproc);
	if (err) {
		dev_err(dev, "Failed to enable clocks\n");
		goto err_clk_put;
	}

	/* Register as a remoteproc device */
	err = rproc_add(rproc);
	if (err) {
		dev_err(dev, "registration of slim remoteproc failed\n");
		goto err_clk_dis;
	}

	return slim_rproc;

err_clk_dis:
	slim_clk_disable(slim_rproc);
err_clk_put:
	for (i = 0; i < ST_SLIM_MAX_CLK && slim_rproc->clks[i]; i++)
		clk_put(slim_rproc->clks[i]);
err:
	rproc_free(rproc);
	return ERR_PTR(err);
}