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
struct tc6387xb_platform_data {int /*<<< orphan*/  (* enable ) (struct platform_device*) ;} ;
struct resource {char* name; scalar_t__ start; int /*<<< orphan*/  flags; scalar_t__ end; } ;
struct tc6387xb {struct resource rscr; int /*<<< orphan*/  scr; struct clk* clk32k; } ;
struct platform_device {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 struct tc6387xb_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tc6387xb*) ; 
 struct tc6387xb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tc6387xb*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 int request_resource (struct resource*,struct resource*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  tc6387xb_cells ; 

__attribute__((used)) static int tc6387xb_probe(struct platform_device *dev)
{
	struct tc6387xb_platform_data *pdata = dev_get_platdata(&dev->dev);
	struct resource *iomem, *rscr;
	struct clk *clk32k;
	struct tc6387xb *tc6387xb;
	int irq, ret;

	iomem = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!iomem)
		return -EINVAL;

	tc6387xb = kzalloc(sizeof(*tc6387xb), GFP_KERNEL);
	if (!tc6387xb)
		return -ENOMEM;

	ret  = platform_get_irq(dev, 0);
	if (ret >= 0)
		irq = ret;
	else
		goto err_no_irq;

	clk32k = clk_get(&dev->dev, "CLK_CK32K");
	if (IS_ERR(clk32k)) {
		ret = PTR_ERR(clk32k);
		goto err_no_clk;
	}

	rscr = &tc6387xb->rscr;
	rscr->name = "tc6387xb-core";
	rscr->start = iomem->start;
	rscr->end = iomem->start + 0xff;
	rscr->flags = IORESOURCE_MEM;

	ret = request_resource(iomem, rscr);
	if (ret)
		goto err_resource;

	tc6387xb->scr = ioremap(rscr->start, resource_size(rscr));
	if (!tc6387xb->scr) {
		ret = -ENOMEM;
		goto err_ioremap;
	}

	tc6387xb->clk32k = clk32k;
	platform_set_drvdata(dev, tc6387xb);

	if (pdata && pdata->enable)
		pdata->enable(dev);

	dev_info(&dev->dev, "Toshiba tc6387xb initialised\n");

	ret = mfd_add_devices(&dev->dev, dev->id, tc6387xb_cells,
			      ARRAY_SIZE(tc6387xb_cells), iomem, irq, NULL);

	if (!ret)
		return 0;

	iounmap(tc6387xb->scr);
err_ioremap:
	release_resource(&tc6387xb->rscr);
err_resource:
	clk_put(clk32k);
err_no_clk:
err_no_irq:
	kfree(tc6387xb);
	return ret;
}