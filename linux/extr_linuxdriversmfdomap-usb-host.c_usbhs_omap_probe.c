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
struct usbhs_omap_platform_data {scalar_t__ nports; int /*<<< orphan*/ * port_mode; } ;
struct usbhs_hcd_omap {int usbhs_rev; scalar_t__ nports; void* init_60m_fclk; void* utmi_p2_gfclk; void* xclk60mhsp2_ck; void* utmi_p1_gfclk; void* xclk60mhsp1_ck; void** hsic60m_clk; void** hsic480m_clk; void** utmi_clk; void* ehci_logic_fck; void* uhh_base; struct usbhs_omap_platform_data* pdata; } ;
struct resource {int dummy; } ;
struct device {scalar_t__ of_node; struct usbhs_omap_platform_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  clkname ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ OMAP3_HS_USB_PORTS ; 
 int /*<<< orphan*/  OMAP_UHH_REVISION ; 
#define  OMAP_USBHS_REV1 129 
#define  OMAP_USBHS_REV2 128 
 int PTR_ERR (void*) ; 
 int clk_set_parent (void*,void*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct usbhs_omap_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__,scalar_t__) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ehci_hsic_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ehci_phy_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ehci_tll_mode (int /*<<< orphan*/ ) ; 
 int of_platform_populate (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  omap_tll_init (struct usbhs_omap_platform_data*) ; 
 int omap_usbhs_alloc_children (struct platform_device*) ; 
 int /*<<< orphan*/  omap_usbhs_init (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usbhs_hcd_omap*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  usbhs_child_match_table ; 
 int usbhs_omap_get_dt_pdata (struct device*,struct usbhs_omap_platform_data*) ; 
 int usbhs_read (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhs_omap_probe(struct platform_device *pdev)
{
	struct device			*dev =  &pdev->dev;
	struct usbhs_omap_platform_data	*pdata = dev_get_platdata(dev);
	struct usbhs_hcd_omap		*omap;
	struct resource			*res;
	int				ret = 0;
	int				i;
	bool				need_logic_fck;

	if (dev->of_node) {
		/* For DT boot we populate platform data from OF node */
		pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;

		ret = usbhs_omap_get_dt_pdata(dev, pdata);
		if (ret)
			return ret;

		dev->platform_data = pdata;
	}

	if (!pdata) {
		dev_err(dev, "Missing platform data\n");
		return -ENODEV;
	}

	if (pdata->nports > OMAP3_HS_USB_PORTS) {
		dev_info(dev, "Too many num_ports <%d> in platform_data. Max %d\n",
				pdata->nports, OMAP3_HS_USB_PORTS);
		return -ENODEV;
	}

	omap = devm_kzalloc(dev, sizeof(*omap), GFP_KERNEL);
	if (!omap) {
		dev_err(dev, "Memory allocation failed\n");
		return -ENOMEM;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	omap->uhh_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(omap->uhh_base))
		return PTR_ERR(omap->uhh_base);

	omap->pdata = pdata;

	/* Initialize the TLL subsystem */
	omap_tll_init(pdata);

	pm_runtime_enable(dev);

	platform_set_drvdata(pdev, omap);
	pm_runtime_get_sync(dev);

	omap->usbhs_rev = usbhs_read(omap->uhh_base, OMAP_UHH_REVISION);

	/* we need to call runtime suspend before we update omap->nports
	 * to prevent unbalanced clk_disable()
	 */
	pm_runtime_put_sync(dev);

	/*
	 * If platform data contains nports then use that
	 * else make out number of ports from USBHS revision
	 */
	if (pdata->nports) {
		omap->nports = pdata->nports;
	} else {
		switch (omap->usbhs_rev) {
		case OMAP_USBHS_REV1:
			omap->nports = 3;
			break;
		case OMAP_USBHS_REV2:
			omap->nports = 2;
			break;
		default:
			omap->nports = OMAP3_HS_USB_PORTS;
			dev_dbg(dev,
			 "USB HOST Rev:0x%x not recognized, assuming %d ports\n",
			 omap->usbhs_rev, omap->nports);
			break;
		}
		pdata->nports = omap->nports;
	}

	i = sizeof(struct clk *) * omap->nports;
	omap->utmi_clk = devm_kzalloc(dev, i, GFP_KERNEL);
	omap->hsic480m_clk = devm_kzalloc(dev, i, GFP_KERNEL);
	omap->hsic60m_clk = devm_kzalloc(dev, i, GFP_KERNEL);

	if (!omap->utmi_clk || !omap->hsic480m_clk || !omap->hsic60m_clk) {
		dev_err(dev, "Memory allocation failed\n");
		ret = -ENOMEM;
		goto err_mem;
	}

	/* Set all clocks as invalid to begin with */
	omap->ehci_logic_fck = ERR_PTR(-ENODEV);
	omap->init_60m_fclk = ERR_PTR(-ENODEV);
	omap->utmi_p1_gfclk = ERR_PTR(-ENODEV);
	omap->utmi_p2_gfclk = ERR_PTR(-ENODEV);
	omap->xclk60mhsp1_ck = ERR_PTR(-ENODEV);
	omap->xclk60mhsp2_ck = ERR_PTR(-ENODEV);

	for (i = 0; i < omap->nports; i++) {
		omap->utmi_clk[i] = ERR_PTR(-ENODEV);
		omap->hsic480m_clk[i] = ERR_PTR(-ENODEV);
		omap->hsic60m_clk[i] = ERR_PTR(-ENODEV);
	}

	/* for OMAP3 i.e. USBHS REV1 */
	if (omap->usbhs_rev == OMAP_USBHS_REV1) {
		need_logic_fck = false;
		for (i = 0; i < omap->nports; i++) {
			if (is_ehci_phy_mode(pdata->port_mode[i]) ||
			    is_ehci_tll_mode(pdata->port_mode[i]) ||
			    is_ehci_hsic_mode(pdata->port_mode[i]))

				need_logic_fck |= true;
		}

		if (need_logic_fck) {
			omap->ehci_logic_fck = devm_clk_get(dev,
							    "usbhost_120m_fck");
			if (IS_ERR(omap->ehci_logic_fck)) {
				ret = PTR_ERR(omap->ehci_logic_fck);
				dev_err(dev, "usbhost_120m_fck failed:%d\n",
					ret);
				goto err_mem;
			}
		}
		goto initialize;
	}

	/* for OMAP4+ i.e. USBHS REV2+ */
	omap->utmi_p1_gfclk = devm_clk_get(dev, "utmi_p1_gfclk");
	if (IS_ERR(omap->utmi_p1_gfclk)) {
		ret = PTR_ERR(omap->utmi_p1_gfclk);
		dev_err(dev, "utmi_p1_gfclk failed error:%d\n", ret);
		goto err_mem;
	}

	omap->utmi_p2_gfclk = devm_clk_get(dev, "utmi_p2_gfclk");
	if (IS_ERR(omap->utmi_p2_gfclk)) {
		ret = PTR_ERR(omap->utmi_p2_gfclk);
		dev_err(dev, "utmi_p2_gfclk failed error:%d\n", ret);
		goto err_mem;
	}

	omap->xclk60mhsp1_ck = devm_clk_get(dev, "refclk_60m_ext_p1");
	if (IS_ERR(omap->xclk60mhsp1_ck)) {
		ret = PTR_ERR(omap->xclk60mhsp1_ck);
		dev_err(dev, "refclk_60m_ext_p1 failed error:%d\n", ret);
		goto err_mem;
	}

	omap->xclk60mhsp2_ck = devm_clk_get(dev, "refclk_60m_ext_p2");
	if (IS_ERR(omap->xclk60mhsp2_ck)) {
		ret = PTR_ERR(omap->xclk60mhsp2_ck);
		dev_err(dev, "refclk_60m_ext_p2 failed error:%d\n", ret);
		goto err_mem;
	}

	omap->init_60m_fclk = devm_clk_get(dev, "refclk_60m_int");
	if (IS_ERR(omap->init_60m_fclk)) {
		ret = PTR_ERR(omap->init_60m_fclk);
		dev_err(dev, "refclk_60m_int failed error:%d\n", ret);
		goto err_mem;
	}

	for (i = 0; i < omap->nports; i++) {
		char clkname[30];

		/* clock names are indexed from 1*/
		snprintf(clkname, sizeof(clkname),
				"usb_host_hs_utmi_p%d_clk", i + 1);

		/* If a clock is not found we won't bail out as not all
		 * platforms have all clocks and we can function without
		 * them
		 */
		omap->utmi_clk[i] = devm_clk_get(dev, clkname);
		if (IS_ERR(omap->utmi_clk[i])) {
			ret = PTR_ERR(omap->utmi_clk[i]);
			dev_err(dev, "Failed to get clock : %s : %d\n",
				clkname, ret);
			goto err_mem;
		}

		snprintf(clkname, sizeof(clkname),
				"usb_host_hs_hsic480m_p%d_clk", i + 1);
		omap->hsic480m_clk[i] = devm_clk_get(dev, clkname);
		if (IS_ERR(omap->hsic480m_clk[i])) {
			ret = PTR_ERR(omap->hsic480m_clk[i]);
			dev_err(dev, "Failed to get clock : %s : %d\n",
				clkname, ret);
			goto err_mem;
		}

		snprintf(clkname, sizeof(clkname),
				"usb_host_hs_hsic60m_p%d_clk", i + 1);
		omap->hsic60m_clk[i] = devm_clk_get(dev, clkname);
		if (IS_ERR(omap->hsic60m_clk[i])) {
			ret = PTR_ERR(omap->hsic60m_clk[i]);
			dev_err(dev, "Failed to get clock : %s : %d\n",
				clkname, ret);
			goto err_mem;
		}
	}

	if (is_ehci_phy_mode(pdata->port_mode[0])) {
		ret = clk_set_parent(omap->utmi_p1_gfclk,
					omap->xclk60mhsp1_ck);
		if (ret != 0) {
			dev_err(dev, "xclk60mhsp1_ck set parent failed: %d\n",
				ret);
			goto err_mem;
		}
	} else if (is_ehci_tll_mode(pdata->port_mode[0])) {
		ret = clk_set_parent(omap->utmi_p1_gfclk,
					omap->init_60m_fclk);
		if (ret != 0) {
			dev_err(dev, "P0 init_60m_fclk set parent failed: %d\n",
				ret);
			goto err_mem;
		}
	}

	if (is_ehci_phy_mode(pdata->port_mode[1])) {
		ret = clk_set_parent(omap->utmi_p2_gfclk,
					omap->xclk60mhsp2_ck);
		if (ret != 0) {
			dev_err(dev, "xclk60mhsp2_ck set parent failed: %d\n",
				ret);
			goto err_mem;
		}
	} else if (is_ehci_tll_mode(pdata->port_mode[1])) {
		ret = clk_set_parent(omap->utmi_p2_gfclk,
						omap->init_60m_fclk);
		if (ret != 0) {
			dev_err(dev, "P1 init_60m_fclk set parent failed: %d\n",
				ret);
			goto err_mem;
		}
	}

initialize:
	omap_usbhs_init(dev);

	if (dev->of_node) {
		ret = of_platform_populate(dev->of_node,
				usbhs_child_match_table, NULL, dev);

		if (ret) {
			dev_err(dev, "Failed to create DT children: %d\n", ret);
			goto err_mem;
		}

	} else {
		ret = omap_usbhs_alloc_children(pdev);
		if (ret) {
			dev_err(dev, "omap_usbhs_alloc_children failed: %d\n",
						ret);
			goto err_mem;
		}
	}

	return 0;

err_mem:
	pm_runtime_disable(dev);

	return ret;
}