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
typedef  int u32 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct mt7601u_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  stat_wq; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  vend_buf; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MT7601U_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_ASIC_VERSION ; 
 int /*<<< orphan*/  MT_EFUSE_CTRL ; 
 int MT_EFUSE_CTRL_SEL ; 
 int /*<<< orphan*/  MT_MAC_CSR0 ; 
 int /*<<< orphan*/  MT_VEND_BUF ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct mt7601u_dev* mt7601u_alloc_device (int /*<<< orphan*/ *) ; 
 int mt7601u_assign_pipes (struct usb_interface*,struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_cleanup (struct mt7601u_dev*) ; 
 int mt7601u_init_hardware (struct mt7601u_dev*) ; 
 int mt7601u_register_device (struct mt7601u_dev*) ; 
 int mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int mt7601u_wait_asic_ready (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_device* usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct mt7601u_dev*) ; 

__attribute__((used)) static int mt7601u_probe(struct usb_interface *usb_intf,
			 const struct usb_device_id *id)
{
	struct usb_device *usb_dev = interface_to_usbdev(usb_intf);
	struct mt7601u_dev *dev;
	u32 asic_rev, mac_rev;
	int ret;

	dev = mt7601u_alloc_device(&usb_intf->dev);
	if (!dev)
		return -ENOMEM;

	usb_dev = usb_get_dev(usb_dev);
	usb_reset_device(usb_dev);

	usb_set_intfdata(usb_intf, dev);

	dev->vend_buf = devm_kmalloc(dev->dev, MT_VEND_BUF, GFP_KERNEL);
	if (!dev->vend_buf) {
		ret = -ENOMEM;
		goto err;
	}

	ret = mt7601u_assign_pipes(usb_intf, dev);
	if (ret)
		goto err;
	ret = mt7601u_wait_asic_ready(dev);
	if (ret)
		goto err;

	asic_rev = mt7601u_rr(dev, MT_ASIC_VERSION);
	mac_rev = mt7601u_rr(dev, MT_MAC_CSR0);
	dev_info(dev->dev, "ASIC revision: %08x MAC revision: %08x\n",
		 asic_rev, mac_rev);
	if ((asic_rev >> 16) != 0x7601) {
		ret = -ENODEV;
		goto err;
	}

	/* Note: vendor driver skips this check for MT7601U */
	if (!(mt7601u_rr(dev, MT_EFUSE_CTRL) & MT_EFUSE_CTRL_SEL))
		dev_warn(dev->dev, "Warning: eFUSE not present\n");

	ret = mt7601u_init_hardware(dev);
	if (ret)
		goto err;
	ret = mt7601u_register_device(dev);
	if (ret)
		goto err_hw;

	set_bit(MT7601U_STATE_INITIALIZED, &dev->state);

	return 0;
err_hw:
	mt7601u_cleanup(dev);
err:
	usb_set_intfdata(usb_intf, NULL);
	usb_put_dev(interface_to_usbdev(usb_intf));

	destroy_workqueue(dev->stat_wq);
	ieee80211_free_hw(dev->hw);
	return ret;
}