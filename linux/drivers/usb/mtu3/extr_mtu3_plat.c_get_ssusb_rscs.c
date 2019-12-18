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
struct otg_switch_mtk {void* manual_drd_enabled; void* is_u3_drd; void* edev; void* role_sw_used; void* vbus; } ;
struct ssusb_mtk {int num_phys; int /*<<< orphan*/  u3p_dis_msk; int /*<<< orphan*/  dr_mode; struct device* dev; void* ippc_base; void** phys; void* dma_clk; void* mcu_clk; void* ref_clk; void* sys_clk; void* vusb33; struct otg_switch_mtk otg_switch; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  USB_DR_MODE_HOST ; 
 int /*<<< orphan*/  USB_DR_MODE_OTG ; 
 int /*<<< orphan*/  USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  USB_DR_MODE_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_clk_get_optional (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_of_phy_get_by_index (struct device*,struct device_node*,int) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 void* extcon_get_edev_by_phandle (struct device*,int /*<<< orphan*/ ) ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int ssusb_wakeup_of_property_parse (struct ssusb_mtk*,struct device_node*) ; 
 int /*<<< orphan*/  usb_get_dr_mode (struct device*) ; 

__attribute__((used)) static int get_ssusb_rscs(struct platform_device *pdev, struct ssusb_mtk *ssusb)
{
	struct device_node *node = pdev->dev.of_node;
	struct otg_switch_mtk *otg_sx = &ssusb->otg_switch;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int i;
	int ret;

	ssusb->vusb33 = devm_regulator_get(dev, "vusb33");
	if (IS_ERR(ssusb->vusb33)) {
		dev_err(dev, "failed to get vusb33\n");
		return PTR_ERR(ssusb->vusb33);
	}

	ssusb->sys_clk = devm_clk_get(dev, "sys_ck");
	if (IS_ERR(ssusb->sys_clk)) {
		dev_err(dev, "failed to get sys clock\n");
		return PTR_ERR(ssusb->sys_clk);
	}

	ssusb->ref_clk = devm_clk_get_optional(dev, "ref_ck");
	if (IS_ERR(ssusb->ref_clk))
		return PTR_ERR(ssusb->ref_clk);

	ssusb->mcu_clk = devm_clk_get_optional(dev, "mcu_ck");
	if (IS_ERR(ssusb->mcu_clk))
		return PTR_ERR(ssusb->mcu_clk);

	ssusb->dma_clk = devm_clk_get_optional(dev, "dma_ck");
	if (IS_ERR(ssusb->dma_clk))
		return PTR_ERR(ssusb->dma_clk);

	ssusb->num_phys = of_count_phandle_with_args(node,
			"phys", "#phy-cells");
	if (ssusb->num_phys > 0) {
		ssusb->phys = devm_kcalloc(dev, ssusb->num_phys,
					sizeof(*ssusb->phys), GFP_KERNEL);
		if (!ssusb->phys)
			return -ENOMEM;
	} else {
		ssusb->num_phys = 0;
	}

	for (i = 0; i < ssusb->num_phys; i++) {
		ssusb->phys[i] = devm_of_phy_get_by_index(dev, node, i);
		if (IS_ERR(ssusb->phys[i])) {
			dev_err(dev, "failed to get phy-%d\n", i);
			return PTR_ERR(ssusb->phys[i]);
		}
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ippc");
	ssusb->ippc_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ssusb->ippc_base))
		return PTR_ERR(ssusb->ippc_base);

	ssusb->dr_mode = usb_get_dr_mode(dev);
	if (ssusb->dr_mode == USB_DR_MODE_UNKNOWN)
		ssusb->dr_mode = USB_DR_MODE_OTG;

	if (ssusb->dr_mode == USB_DR_MODE_PERIPHERAL)
		goto out;

	/* if host role is supported */
	ret = ssusb_wakeup_of_property_parse(ssusb, node);
	if (ret) {
		dev_err(dev, "failed to parse uwk property\n");
		return ret;
	}

	/* optional property, ignore the error if it does not exist */
	of_property_read_u32(node, "mediatek,u3p-dis-msk",
			     &ssusb->u3p_dis_msk);

	otg_sx->vbus = devm_regulator_get(dev, "vbus");
	if (IS_ERR(otg_sx->vbus)) {
		dev_err(dev, "failed to get vbus\n");
		return PTR_ERR(otg_sx->vbus);
	}

	if (ssusb->dr_mode == USB_DR_MODE_HOST)
		goto out;

	/* if dual-role mode is supported */
	otg_sx->is_u3_drd = of_property_read_bool(node, "mediatek,usb3-drd");
	otg_sx->manual_drd_enabled =
		of_property_read_bool(node, "enable-manual-drd");
	otg_sx->role_sw_used = of_property_read_bool(node, "usb-role-switch");

	if (!otg_sx->role_sw_used && of_property_read_bool(node, "extcon")) {
		otg_sx->edev = extcon_get_edev_by_phandle(ssusb->dev, 0);
		if (IS_ERR(otg_sx->edev)) {
			dev_err(ssusb->dev, "couldn't get extcon device\n");
			return PTR_ERR(otg_sx->edev);
		}
	}

out:
	dev_info(dev, "dr_mode: %d, is_u3_dr: %d, u3p_dis_msk: %x, drd: %s\n",
		ssusb->dr_mode, otg_sx->is_u3_drd, ssusb->u3p_dis_msk,
		otg_sx->manual_drd_enabled ? "manual" : "auto");

	return 0;
}