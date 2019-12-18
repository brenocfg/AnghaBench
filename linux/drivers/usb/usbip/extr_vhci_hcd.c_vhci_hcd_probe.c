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
struct vhci {int /*<<< orphan*/ * vhci_hcd_ss; int /*<<< orphan*/ * vhci_hcd_hs; } ;
struct usb_hcd {int has_tt; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_shared_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*,...) ; 
 int /*<<< orphan*/  vhci_hc_driver ; 

__attribute__((used)) static int vhci_hcd_probe(struct platform_device *pdev)
{
	struct vhci             *vhci = *((void **)dev_get_platdata(&pdev->dev));
	struct usb_hcd		*hcd_hs;
	struct usb_hcd		*hcd_ss;
	int			ret;

	usbip_dbg_vhci_hc("name %s id %d\n", pdev->name, pdev->id);

	/*
	 * Allocate and initialize hcd.
	 * Our private data is also allocated automatically.
	 */
	hcd_hs = usb_create_hcd(&vhci_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd_hs) {
		pr_err("create primary hcd failed\n");
		return -ENOMEM;
	}
	hcd_hs->has_tt = 1;

	/*
	 * Finish generic HCD structure initialization and register.
	 * Call the driver's reset() and start() routines.
	 */
	ret = usb_add_hcd(hcd_hs, 0, 0);
	if (ret != 0) {
		pr_err("usb_add_hcd hs failed %d\n", ret);
		goto put_usb2_hcd;
	}

	hcd_ss = usb_create_shared_hcd(&vhci_hc_driver, &pdev->dev,
				       dev_name(&pdev->dev), hcd_hs);
	if (!hcd_ss) {
		ret = -ENOMEM;
		pr_err("create shared hcd failed\n");
		goto remove_usb2_hcd;
	}

	ret = usb_add_hcd(hcd_ss, 0, 0);
	if (ret) {
		pr_err("usb_add_hcd ss failed %d\n", ret);
		goto put_usb3_hcd;
	}

	usbip_dbg_vhci_hc("bye\n");
	return 0;

put_usb3_hcd:
	usb_put_hcd(hcd_ss);
remove_usb2_hcd:
	usb_remove_hcd(hcd_hs);
put_usb2_hcd:
	usb_put_hcd(hcd_hs);
	vhci->vhci_hcd_hs = NULL;
	vhci->vhci_hcd_ss = NULL;
	return ret;
}