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
struct sti_hqvdp {int /*<<< orphan*/  vtg; void* reset; void* clk_pix_main; void* clk; int /*<<< orphan*/  regs; struct device* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sti_hqvdp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_vtg_find (struct device_node*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sti_hqvdp*) ; 
 int /*<<< orphan*/  reset_control_deassert (void*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sti_hqvdp_ops ; 

__attribute__((used)) static int sti_hqvdp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *vtg_np;
	struct sti_hqvdp *hqvdp;
	struct resource *res;

	DRM_DEBUG_DRIVER("\n");

	hqvdp = devm_kzalloc(dev, sizeof(*hqvdp), GFP_KERNEL);
	if (!hqvdp) {
		DRM_ERROR("Failed to allocate HQVDP context\n");
		return -ENOMEM;
	}

	hqvdp->dev = dev;

	/* Get Memory resources */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		DRM_ERROR("Get memory resource failed\n");
		return -ENXIO;
	}
	hqvdp->regs = devm_ioremap(dev, res->start, resource_size(res));
	if (!hqvdp->regs) {
		DRM_ERROR("Register mapping failed\n");
		return -ENXIO;
	}

	/* Get clock resources */
	hqvdp->clk = devm_clk_get(dev, "hqvdp");
	hqvdp->clk_pix_main = devm_clk_get(dev, "pix_main");
	if (IS_ERR(hqvdp->clk) || IS_ERR(hqvdp->clk_pix_main)) {
		DRM_ERROR("Cannot get clocks\n");
		return -ENXIO;
	}

	/* Get reset resources */
	hqvdp->reset = devm_reset_control_get(dev, "hqvdp");
	if (!IS_ERR(hqvdp->reset))
		reset_control_deassert(hqvdp->reset);

	vtg_np = of_parse_phandle(pdev->dev.of_node, "st,vtg", 0);
	if (vtg_np)
		hqvdp->vtg = of_vtg_find(vtg_np);
	of_node_put(vtg_np);

	platform_set_drvdata(pdev, hqvdp);

	return component_add(&pdev->dev, &sti_hqvdp_ops);
}