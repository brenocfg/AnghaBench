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
typedef  int u8 ;
typedef  int u16 ;
struct work_struct {int dummy; } ;
struct device {int dummy; } ;
struct usb_device {struct device dev; } ;
struct most_dev {int /*<<< orphan*/  iface; int /*<<< orphan*/  (* on_netinfo ) (int /*<<< orphan*/ *,int,int*) ;struct usb_device* usb_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRCI_REG_HW_ADDR_HI ; 
 int /*<<< orphan*/  DRCI_REG_HW_ADDR_LO ; 
 int /*<<< orphan*/  DRCI_REG_HW_ADDR_MI ; 
 int /*<<< orphan*/  DRCI_REG_NI_STATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ drci_rd_reg (struct usb_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int*) ; 
 struct most_dev* to_mdev_from_work (struct work_struct*) ; 

__attribute__((used)) static void wq_netinfo(struct work_struct *wq_obj)
{
	struct most_dev *mdev = to_mdev_from_work(wq_obj);
	struct usb_device *usb_device = mdev->usb_device;
	struct device *dev = &usb_device->dev;
	u16 hi, mi, lo, link;
	u8 hw_addr[6];

	if (drci_rd_reg(usb_device, DRCI_REG_HW_ADDR_HI, &hi) < 0) {
		dev_err(dev, "Vendor request 'hw_addr_hi' failed\n");
		return;
	}

	if (drci_rd_reg(usb_device, DRCI_REG_HW_ADDR_MI, &mi) < 0) {
		dev_err(dev, "Vendor request 'hw_addr_mid' failed\n");
		return;
	}

	if (drci_rd_reg(usb_device, DRCI_REG_HW_ADDR_LO, &lo) < 0) {
		dev_err(dev, "Vendor request 'hw_addr_low' failed\n");
		return;
	}

	if (drci_rd_reg(usb_device, DRCI_REG_NI_STATE, &link) < 0) {
		dev_err(dev, "Vendor request 'link status' failed\n");
		return;
	}

	hw_addr[0] = hi >> 8;
	hw_addr[1] = hi;
	hw_addr[2] = mi >> 8;
	hw_addr[3] = mi;
	hw_addr[4] = lo >> 8;
	hw_addr[5] = lo;

	if (mdev->on_netinfo)
		mdev->on_netinfo(&mdev->iface, link, hw_addr);
}