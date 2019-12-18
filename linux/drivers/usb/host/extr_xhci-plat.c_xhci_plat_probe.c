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
struct xhci_plat_priv {int dummy; } ;
struct xhci_hcd {int imod_interval; int /*<<< orphan*/ * reg_clk; int /*<<< orphan*/ * clk; struct usb_hcd* shared_hcd; int /*<<< orphan*/  hcc_params; int /*<<< orphan*/  quirks; struct usb_hcd* main_hcd; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int can_do_streams; int /*<<< orphan*/ * usb_phy; int /*<<< orphan*/  tpl_support; TYPE_1__ self; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; int /*<<< orphan*/ * regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/ * bus; int /*<<< orphan*/  fwnode; } ;
struct platform_device {struct device dev; } ;
struct hc_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int HCC_MAX_PSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  XHCI_BROKEN_PORT_PED ; 
 int /*<<< orphan*/  XHCI_HW_LPM_DISABLE ; 
 int /*<<< orphan*/  XHCI_LPM_SUPPORT ; 
 void* __usb_create_hcd (struct hc_driver const*,struct device*,struct device*,int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (struct device*) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 void* devm_clk_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/ * devm_usb_get_phy_by_phandle (struct device*,char*,int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 struct xhci_plat_priv* hcd_to_xhci_priv (struct usb_hcd*) ; 
 scalar_t__ is_acpi_device_node (int /*<<< orphan*/ ) ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 
 struct xhci_plat_priv* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_usb_host_tpl_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int usb_phy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 
 struct hc_driver xhci_plat_hc_driver ; 

__attribute__((used)) static int xhci_plat_probe(struct platform_device *pdev)
{
	const struct xhci_plat_priv *priv_match;
	const struct hc_driver	*driver;
	struct device		*sysdev, *tmpdev;
	struct xhci_hcd		*xhci;
	struct resource         *res;
	struct usb_hcd		*hcd;
	int			ret;
	int			irq;

	if (usb_disabled())
		return -ENODEV;

	driver = &xhci_plat_hc_driver;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	/*
	 * sysdev must point to a device that is known to the system firmware
	 * or PCI hardware. We handle these three cases here:
	 * 1. xhci_plat comes from firmware
	 * 2. xhci_plat is child of a device from firmware (dwc3-plat)
	 * 3. xhci_plat is grandchild of a pci device (dwc3-pci)
	 */
	for (sysdev = &pdev->dev; sysdev; sysdev = sysdev->parent) {
		if (is_of_node(sysdev->fwnode) ||
			is_acpi_device_node(sysdev->fwnode))
			break;
#ifdef CONFIG_PCI
		else if (sysdev->bus == &pci_bus_type)
			break;
#endif
	}

	if (!sysdev)
		sysdev = &pdev->dev;

	/* Try to set 64-bit DMA first */
	if (WARN_ON(!sysdev->dma_mask))
		/* Platform did not initialize dma_mask */
		ret = dma_coerce_mask_and_coherent(sysdev,
						   DMA_BIT_MASK(64));
	else
		ret = dma_set_mask_and_coherent(sysdev, DMA_BIT_MASK(64));

	/* If seting 64-bit DMA mask fails, fall back to 32-bit DMA mask */
	if (ret) {
		ret = dma_set_mask_and_coherent(sysdev, DMA_BIT_MASK(32));
		if (ret)
			return ret;
	}

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_noresume(&pdev->dev);

	hcd = __usb_create_hcd(driver, sysdev, &pdev->dev,
			       dev_name(&pdev->dev), NULL);
	if (!hcd) {
		ret = -ENOMEM;
		goto disable_runtime;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hcd->regs)) {
		ret = PTR_ERR(hcd->regs);
		goto put_hcd;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	xhci = hcd_to_xhci(hcd);

	/*
	 * Not all platforms have clks so it is not an error if the
	 * clock do not exist.
	 */
	xhci->reg_clk = devm_clk_get_optional(&pdev->dev, "reg");
	if (IS_ERR(xhci->reg_clk)) {
		ret = PTR_ERR(xhci->reg_clk);
		goto put_hcd;
	}

	ret = clk_prepare_enable(xhci->reg_clk);
	if (ret)
		goto put_hcd;

	xhci->clk = devm_clk_get_optional(&pdev->dev, NULL);
	if (IS_ERR(xhci->clk)) {
		ret = PTR_ERR(xhci->clk);
		goto disable_reg_clk;
	}

	ret = clk_prepare_enable(xhci->clk);
	if (ret)
		goto disable_reg_clk;

	priv_match = of_device_get_match_data(&pdev->dev);
	if (priv_match) {
		struct xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

		/* Just copy data for now */
		if (priv_match)
			*priv = *priv_match;
	}

	device_wakeup_enable(hcd->self.controller);

	xhci->main_hcd = hcd;
	xhci->shared_hcd = __usb_create_hcd(driver, sysdev, &pdev->dev,
			dev_name(&pdev->dev), hcd);
	if (!xhci->shared_hcd) {
		ret = -ENOMEM;
		goto disable_clk;
	}

	/* imod_interval is the interrupt moderation value in nanoseconds. */
	xhci->imod_interval = 40000;

	/* Iterate over all parent nodes for finding quirks */
	for (tmpdev = &pdev->dev; tmpdev; tmpdev = tmpdev->parent) {

		if (device_property_read_bool(tmpdev, "usb2-lpm-disable"))
			xhci->quirks |= XHCI_HW_LPM_DISABLE;

		if (device_property_read_bool(tmpdev, "usb3-lpm-capable"))
			xhci->quirks |= XHCI_LPM_SUPPORT;

		if (device_property_read_bool(tmpdev, "quirk-broken-port-ped"))
			xhci->quirks |= XHCI_BROKEN_PORT_PED;

		device_property_read_u32(tmpdev, "imod-interval-ns",
					 &xhci->imod_interval);
	}

	hcd->usb_phy = devm_usb_get_phy_by_phandle(sysdev, "usb-phy", 0);
	if (IS_ERR(hcd->usb_phy)) {
		ret = PTR_ERR(hcd->usb_phy);
		if (ret == -EPROBE_DEFER)
			goto put_usb3_hcd;
		hcd->usb_phy = NULL;
	} else {
		ret = usb_phy_init(hcd->usb_phy);
		if (ret)
			goto put_usb3_hcd;
	}

	hcd->tpl_support = of_usb_host_tpl_support(sysdev->of_node);
	xhci->shared_hcd->tpl_support = hcd->tpl_support;
	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (ret)
		goto disable_usb_phy;

	if (HCC_MAX_PSA(xhci->hcc_params) >= 4)
		xhci->shared_hcd->can_do_streams = 1;

	ret = usb_add_hcd(xhci->shared_hcd, irq, IRQF_SHARED);
	if (ret)
		goto dealloc_usb2_hcd;

	device_enable_async_suspend(&pdev->dev);
	pm_runtime_put_noidle(&pdev->dev);

	/*
	 * Prevent runtime pm from being on as default, users should enable
	 * runtime pm using power/control in sysfs.
	 */
	pm_runtime_forbid(&pdev->dev);

	return 0;


dealloc_usb2_hcd:
	usb_remove_hcd(hcd);

disable_usb_phy:
	usb_phy_shutdown(hcd->usb_phy);

put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);

disable_clk:
	clk_disable_unprepare(xhci->clk);

disable_reg_clk:
	clk_disable_unprepare(xhci->reg_clk);

put_hcd:
	usb_put_hcd(hcd);

disable_runtime:
	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return ret;
}