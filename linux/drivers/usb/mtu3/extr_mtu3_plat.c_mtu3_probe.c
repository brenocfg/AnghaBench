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
struct ssusb_mtk {int dr_mode; int is_host; struct device* dev; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_USB_MTU3_GADGET ; 
 int /*<<< orphan*/  CONFIG_USB_MTU3_HOST ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_enable_async_suspend (struct device*) ; 
 struct ssusb_mtk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int get_ssusb_rscs (struct platform_device*,struct ssusb_mtk*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ssusb_mtk*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  ssusb_debugfs_create_root (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_debugfs_remove_root (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_gadget_exit (struct ssusb_mtk*) ; 
 int ssusb_gadget_init (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_host_exit (struct ssusb_mtk*) ; 
 int ssusb_host_init (struct ssusb_mtk*,struct device_node*) ; 
 int /*<<< orphan*/  ssusb_ip_sw_reset (struct ssusb_mtk*) ; 
 int ssusb_otg_switch_init (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_rscs_exit (struct ssusb_mtk*) ; 
 int ssusb_rscs_init (struct ssusb_mtk*) ; 

__attribute__((used)) static int mtu3_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct ssusb_mtk *ssusb;
	int ret = -ENOMEM;

	/* all elements are set to ZERO as default value */
	ssusb = devm_kzalloc(dev, sizeof(*ssusb), GFP_KERNEL);
	if (!ssusb)
		return -ENOMEM;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_err(dev, "No suitable DMA config available\n");
		return -ENOTSUPP;
	}

	platform_set_drvdata(pdev, ssusb);
	ssusb->dev = dev;

	ret = get_ssusb_rscs(pdev, ssusb);
	if (ret)
		return ret;

	ssusb_debugfs_create_root(ssusb);

	/* enable power domain */
	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);
	device_enable_async_suspend(dev);

	ret = ssusb_rscs_init(ssusb);
	if (ret)
		goto comm_init_err;

	ssusb_ip_sw_reset(ssusb);

	if (IS_ENABLED(CONFIG_USB_MTU3_HOST))
		ssusb->dr_mode = USB_DR_MODE_HOST;
	else if (IS_ENABLED(CONFIG_USB_MTU3_GADGET))
		ssusb->dr_mode = USB_DR_MODE_PERIPHERAL;

	/* default as host */
	ssusb->is_host = !(ssusb->dr_mode == USB_DR_MODE_PERIPHERAL);

	switch (ssusb->dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
		ret = ssusb_gadget_init(ssusb);
		if (ret) {
			dev_err(dev, "failed to initialize gadget\n");
			goto comm_exit;
		}
		break;
	case USB_DR_MODE_HOST:
		ret = ssusb_host_init(ssusb, node);
		if (ret) {
			dev_err(dev, "failed to initialize host\n");
			goto comm_exit;
		}
		break;
	case USB_DR_MODE_OTG:
		ret = ssusb_gadget_init(ssusb);
		if (ret) {
			dev_err(dev, "failed to initialize gadget\n");
			goto comm_exit;
		}

		ret = ssusb_host_init(ssusb, node);
		if (ret) {
			dev_err(dev, "failed to initialize host\n");
			goto gadget_exit;
		}

		ret = ssusb_otg_switch_init(ssusb);
		if (ret) {
			dev_err(dev, "failed to initialize switch\n");
			goto host_exit;
		}
		break;
	default:
		dev_err(dev, "unsupported mode: %d\n", ssusb->dr_mode);
		ret = -EINVAL;
		goto comm_exit;
	}

	return 0;

host_exit:
	ssusb_host_exit(ssusb);
gadget_exit:
	ssusb_gadget_exit(ssusb);
comm_exit:
	ssusb_rscs_exit(ssusb);
comm_init_err:
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);
	ssusb_debugfs_remove_root(ssusb);

	return ret;
}