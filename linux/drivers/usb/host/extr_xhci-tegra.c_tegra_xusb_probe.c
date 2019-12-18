#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_28__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
struct xhci_hcd {TYPE_3__* shared_hcd; } ;
struct tegra_xusb_mbox_msg {scalar_t__ data; int /*<<< orphan*/  cmd; } ;
struct tegra_xusb_fw_header {int dummy; } ;
struct tegra_xusb {scalar_t__ xhci_irq; scalar_t__ mbox_irq; unsigned int num_phys; struct phy* padctl; TYPE_3__* hcd; int /*<<< orphan*/  lock; struct phy* regs; TYPE_6__* dev; struct phy** phys; TYPE_21__* soc; TYPE_28__* supplies; struct phy* host_rst; struct phy* host_clk; struct phy* ss_rst; struct phy* ss_clk; struct phy* pll_e; struct phy* clk_m; struct phy* pll_u_480m; struct phy* fs_src_clk; struct phy* hs_src_clk; struct phy* ss_src_clk; struct phy* falcon_clk; struct phy* ipfs_base; struct phy* fpci_base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_41__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_6__ dev; } ;
struct phy {int dummy; } ;
typedef  int /*<<< orphan*/  prop ;
struct TYPE_39__ {int /*<<< orphan*/  controller; } ;
struct TYPE_40__ {TYPE_2__ self; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; struct phy* regs; } ;
struct TYPE_38__ {int /*<<< orphan*/  supply; } ;
struct TYPE_37__ {unsigned int num_supplies; unsigned int num_types; TYPE_1__* phy_types; int /*<<< orphan*/ * supply_names; scalar_t__ has_ipfs; } ;
struct TYPE_36__ {unsigned int num; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int /*<<< orphan*/  MBOX_CMD_MSG_ENABLED ; 
 int PTR_ERR (struct phy*) ; 
 int /*<<< orphan*/  TEGRA_POWERGATE_XUSBA ; 
 int /*<<< orphan*/  TEGRA_POWERGATE_XUSBC ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 void* devm_clk_get (TYPE_6__*,char*) ; 
 void* devm_ioremap_resource (TYPE_6__*,struct resource*) ; 
 void* devm_kcalloc (TYPE_6__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct tegra_xusb* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_optional_get (TYPE_6__*,char*) ; 
 int devm_regulator_bulk_get (TYPE_6__*,unsigned int,TYPE_28__*) ; 
 int devm_request_threaded_irq (TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_xusb*) ; 
 void* devm_reset_control_get (TYPE_6__*,char*) ; 
 int dma_set_mask_and_coherent (TYPE_6__*,int /*<<< orphan*/ ) ; 
 struct xhci_hcd* hcd_to_xhci (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_21__* of_device_get_match_data (TYPE_6__*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_xusb*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_6__*) ; 
 scalar_t__ pm_runtime_enabled (TYPE_6__*) ; 
 int pm_runtime_get_sync (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (TYPE_6__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 
 int tegra_powergate_sequence_power_up (int /*<<< orphan*/ ,struct phy*,struct phy*) ; 
 int /*<<< orphan*/  tegra_xhci_hc_driver ; 
 int /*<<< orphan*/  tegra_xusb_config (struct tegra_xusb*,struct resource*) ; 
 int tegra_xusb_load_firmware (struct tegra_xusb*) ; 
 int /*<<< orphan*/  tegra_xusb_mbox_irq ; 
 int tegra_xusb_mbox_send (struct tegra_xusb*,struct tegra_xusb_mbox_msg*) ; 
 int /*<<< orphan*/  tegra_xusb_mbox_thread ; 
 struct phy* tegra_xusb_padctl_get (TYPE_6__*) ; 
 int /*<<< orphan*/  tegra_xusb_padctl_put (struct phy*) ; 
 int tegra_xusb_powerdomain_init (TYPE_6__*,struct tegra_xusb*) ; 
 int /*<<< orphan*/  tegra_xusb_powerdomain_remove (TYPE_6__*,struct tegra_xusb*) ; 
 int tegra_xusb_runtime_resume (TYPE_6__*) ; 
 int /*<<< orphan*/  tegra_xusb_runtime_suspend (TYPE_6__*) ; 
 int usb_add_hcd (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* usb_create_hcd (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* usb_create_shared_hcd (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  usb_put_hcd (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_remove_hcd (TYPE_3__*) ; 

__attribute__((used)) static int tegra_xusb_probe(struct platform_device *pdev)
{
	struct tegra_xusb_mbox_msg msg;
	struct resource *res, *regs;
	struct tegra_xusb *tegra;
	struct xhci_hcd *xhci;
	unsigned int i, j, k;
	struct phy *phy;
	int err;

	BUILD_BUG_ON(sizeof(struct tegra_xusb_fw_header) != 256);

	tegra = devm_kzalloc(&pdev->dev, sizeof(*tegra), GFP_KERNEL);
	if (!tegra)
		return -ENOMEM;

	tegra->soc = of_device_get_match_data(&pdev->dev);
	mutex_init(&tegra->lock);
	tegra->dev = &pdev->dev;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	tegra->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(tegra->regs))
		return PTR_ERR(tegra->regs);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	tegra->fpci_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(tegra->fpci_base))
		return PTR_ERR(tegra->fpci_base);

	if (tegra->soc->has_ipfs) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
		tegra->ipfs_base = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(tegra->ipfs_base))
			return PTR_ERR(tegra->ipfs_base);
	}

	tegra->xhci_irq = platform_get_irq(pdev, 0);
	if (tegra->xhci_irq < 0)
		return tegra->xhci_irq;

	tegra->mbox_irq = platform_get_irq(pdev, 1);
	if (tegra->mbox_irq < 0)
		return tegra->mbox_irq;

	tegra->padctl = tegra_xusb_padctl_get(&pdev->dev);
	if (IS_ERR(tegra->padctl))
		return PTR_ERR(tegra->padctl);

	tegra->host_clk = devm_clk_get(&pdev->dev, "xusb_host");
	if (IS_ERR(tegra->host_clk)) {
		err = PTR_ERR(tegra->host_clk);
		dev_err(&pdev->dev, "failed to get xusb_host: %d\n", err);
		goto put_padctl;
	}

	tegra->falcon_clk = devm_clk_get(&pdev->dev, "xusb_falcon_src");
	if (IS_ERR(tegra->falcon_clk)) {
		err = PTR_ERR(tegra->falcon_clk);
		dev_err(&pdev->dev, "failed to get xusb_falcon_src: %d\n", err);
		goto put_padctl;
	}

	tegra->ss_clk = devm_clk_get(&pdev->dev, "xusb_ss");
	if (IS_ERR(tegra->ss_clk)) {
		err = PTR_ERR(tegra->ss_clk);
		dev_err(&pdev->dev, "failed to get xusb_ss: %d\n", err);
		goto put_padctl;
	}

	tegra->ss_src_clk = devm_clk_get(&pdev->dev, "xusb_ss_src");
	if (IS_ERR(tegra->ss_src_clk)) {
		err = PTR_ERR(tegra->ss_src_clk);
		dev_err(&pdev->dev, "failed to get xusb_ss_src: %d\n", err);
		goto put_padctl;
	}

	tegra->hs_src_clk = devm_clk_get(&pdev->dev, "xusb_hs_src");
	if (IS_ERR(tegra->hs_src_clk)) {
		err = PTR_ERR(tegra->hs_src_clk);
		dev_err(&pdev->dev, "failed to get xusb_hs_src: %d\n", err);
		goto put_padctl;
	}

	tegra->fs_src_clk = devm_clk_get(&pdev->dev, "xusb_fs_src");
	if (IS_ERR(tegra->fs_src_clk)) {
		err = PTR_ERR(tegra->fs_src_clk);
		dev_err(&pdev->dev, "failed to get xusb_fs_src: %d\n", err);
		goto put_padctl;
	}

	tegra->pll_u_480m = devm_clk_get(&pdev->dev, "pll_u_480m");
	if (IS_ERR(tegra->pll_u_480m)) {
		err = PTR_ERR(tegra->pll_u_480m);
		dev_err(&pdev->dev, "failed to get pll_u_480m: %d\n", err);
		goto put_padctl;
	}

	tegra->clk_m = devm_clk_get(&pdev->dev, "clk_m");
	if (IS_ERR(tegra->clk_m)) {
		err = PTR_ERR(tegra->clk_m);
		dev_err(&pdev->dev, "failed to get clk_m: %d\n", err);
		goto put_padctl;
	}

	tegra->pll_e = devm_clk_get(&pdev->dev, "pll_e");
	if (IS_ERR(tegra->pll_e)) {
		err = PTR_ERR(tegra->pll_e);
		dev_err(&pdev->dev, "failed to get pll_e: %d\n", err);
		goto put_padctl;
	}

	if (!of_property_read_bool(pdev->dev.of_node, "power-domains")) {
		tegra->host_rst = devm_reset_control_get(&pdev->dev,
							 "xusb_host");
		if (IS_ERR(tegra->host_rst)) {
			err = PTR_ERR(tegra->host_rst);
			dev_err(&pdev->dev,
				"failed to get xusb_host reset: %d\n", err);
			goto put_padctl;
		}

		tegra->ss_rst = devm_reset_control_get(&pdev->dev, "xusb_ss");
		if (IS_ERR(tegra->ss_rst)) {
			err = PTR_ERR(tegra->ss_rst);
			dev_err(&pdev->dev, "failed to get xusb_ss reset: %d\n",
				err);
			goto put_padctl;
		}

		err = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_XUSBA,
							tegra->ss_clk,
							tegra->ss_rst);
		if (err) {
			dev_err(&pdev->dev,
				"failed to enable XUSBA domain: %d\n", err);
			goto put_padctl;
		}

		err = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_XUSBC,
							tegra->host_clk,
							tegra->host_rst);
		if (err) {
			tegra_powergate_power_off(TEGRA_POWERGATE_XUSBA);
			dev_err(&pdev->dev,
				"failed to enable XUSBC domain: %d\n", err);
			goto put_padctl;
		}
	} else {
		err = tegra_xusb_powerdomain_init(&pdev->dev, tegra);
		if (err)
			goto put_powerdomains;
	}

	tegra->supplies = devm_kcalloc(&pdev->dev, tegra->soc->num_supplies,
				       sizeof(*tegra->supplies), GFP_KERNEL);
	if (!tegra->supplies) {
		err = -ENOMEM;
		goto put_powerdomains;
	}

	for (i = 0; i < tegra->soc->num_supplies; i++)
		tegra->supplies[i].supply = tegra->soc->supply_names[i];

	err = devm_regulator_bulk_get(&pdev->dev, tegra->soc->num_supplies,
				      tegra->supplies);
	if (err) {
		dev_err(&pdev->dev, "failed to get regulators: %d\n", err);
		goto put_powerdomains;
	}

	for (i = 0; i < tegra->soc->num_types; i++)
		tegra->num_phys += tegra->soc->phy_types[i].num;

	tegra->phys = devm_kcalloc(&pdev->dev, tegra->num_phys,
				   sizeof(*tegra->phys), GFP_KERNEL);
	if (!tegra->phys) {
		err = -ENOMEM;
		goto put_powerdomains;
	}

	for (i = 0, k = 0; i < tegra->soc->num_types; i++) {
		char prop[8];

		for (j = 0; j < tegra->soc->phy_types[i].num; j++) {
			snprintf(prop, sizeof(prop), "%s-%d",
				 tegra->soc->phy_types[i].name, j);

			phy = devm_phy_optional_get(&pdev->dev, prop);
			if (IS_ERR(phy)) {
				dev_err(&pdev->dev,
					"failed to get PHY %s: %ld\n", prop,
					PTR_ERR(phy));
				err = PTR_ERR(phy);
				goto put_powerdomains;
			}

			tegra->phys[k++] = phy;
		}
	}

	tegra->hcd = usb_create_hcd(&tegra_xhci_hc_driver, &pdev->dev,
				    dev_name(&pdev->dev));
	if (!tegra->hcd) {
		err = -ENOMEM;
		goto put_powerdomains;
	}

	/*
	 * This must happen after usb_create_hcd(), because usb_create_hcd()
	 * will overwrite the drvdata of the device with the hcd it creates.
	 */
	platform_set_drvdata(pdev, tegra);

	pm_runtime_enable(&pdev->dev);
	if (pm_runtime_enabled(&pdev->dev))
		err = pm_runtime_get_sync(&pdev->dev);
	else
		err = tegra_xusb_runtime_resume(&pdev->dev);

	if (err < 0) {
		dev_err(&pdev->dev, "failed to enable device: %d\n", err);
		goto disable_rpm;
	}

	tegra_xusb_config(tegra, regs);

	/*
	 * The XUSB Falcon microcontroller can only address 40 bits, so set
	 * the DMA mask accordingly.
	 */
	err = dma_set_mask_and_coherent(tegra->dev, DMA_BIT_MASK(40));
	if (err < 0) {
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", err);
		goto put_rpm;
	}

	err = tegra_xusb_load_firmware(tegra);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to load firmware: %d\n", err);
		goto put_rpm;
	}

	tegra->hcd->regs = tegra->regs;
	tegra->hcd->rsrc_start = regs->start;
	tegra->hcd->rsrc_len = resource_size(regs);

	err = usb_add_hcd(tegra->hcd, tegra->xhci_irq, IRQF_SHARED);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to add USB HCD: %d\n", err);
		goto put_rpm;
	}

	device_wakeup_enable(tegra->hcd->self.controller);

	xhci = hcd_to_xhci(tegra->hcd);

	xhci->shared_hcd = usb_create_shared_hcd(&tegra_xhci_hc_driver,
						 &pdev->dev,
						 dev_name(&pdev->dev),
						 tegra->hcd);
	if (!xhci->shared_hcd) {
		dev_err(&pdev->dev, "failed to create shared HCD\n");
		err = -ENOMEM;
		goto remove_usb2;
	}

	err = usb_add_hcd(xhci->shared_hcd, tegra->xhci_irq, IRQF_SHARED);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to add shared HCD: %d\n", err);
		goto put_usb3;
	}

	mutex_lock(&tegra->lock);

	/* Enable firmware messages from controller. */
	msg.cmd = MBOX_CMD_MSG_ENABLED;
	msg.data = 0;

	err = tegra_xusb_mbox_send(tegra, &msg);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to enable messages: %d\n", err);
		mutex_unlock(&tegra->lock);
		goto remove_usb3;
	}

	mutex_unlock(&tegra->lock);

	err = devm_request_threaded_irq(&pdev->dev, tegra->mbox_irq,
					tegra_xusb_mbox_irq,
					tegra_xusb_mbox_thread, 0,
					dev_name(&pdev->dev), tegra);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", err);
		goto remove_usb3;
	}

	return 0;

remove_usb3:
	usb_remove_hcd(xhci->shared_hcd);
put_usb3:
	usb_put_hcd(xhci->shared_hcd);
remove_usb2:
	usb_remove_hcd(tegra->hcd);
put_rpm:
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra_xusb_runtime_suspend(&pdev->dev);
disable_rpm:
	pm_runtime_disable(&pdev->dev);
	usb_put_hcd(tegra->hcd);
put_powerdomains:
	if (!of_property_read_bool(pdev->dev.of_node, "power-domains")) {
		tegra_powergate_power_off(TEGRA_POWERGATE_XUSBC);
		tegra_powergate_power_off(TEGRA_POWERGATE_XUSBA);
	} else {
		tegra_xusb_powerdomain_remove(&pdev->dev, tegra);
	}
put_padctl:
	tegra_xusb_padctl_put(tegra->padctl);
	return err;
}