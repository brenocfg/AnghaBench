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
typedef  int u32 ;
struct usbnet {int /*<<< orphan*/  net; scalar_t__* data; } ;
struct usb_interface {int dummy; } ;
struct smsc95xx_priv {int suspend_flags; int /*<<< orphan*/  carrier_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CARRIER_CHECK_DELAY ; 
 int PM_CTL_WOL_EN_ ; 
 int PM_CTL_WUPS_ ; 
 int /*<<< orphan*/  PM_CTRL ; 
 int SUSPEND_ALLMODES ; 
 int /*<<< orphan*/  WUCSR ; 
 int WUCSR_MPEN_ ; 
 int WUCSR_WAKE_EN_ ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int smsc95xx_read_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc95xx_write_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usbnet_resume (struct usb_interface*) ; 

__attribute__((used)) static int smsc95xx_resume(struct usb_interface *intf)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct smsc95xx_priv *pdata;
	u8 suspend_flags;
	int ret;
	u32 val;

	BUG_ON(!dev);
	pdata = (struct smsc95xx_priv *)(dev->data[0]);
	suspend_flags = pdata->suspend_flags;

	netdev_dbg(dev->net, "resume suspend_flags=0x%02x\n", suspend_flags);

	/* do this first to ensure it's cleared even in error case */
	pdata->suspend_flags = 0;
	schedule_delayed_work(&pdata->carrier_check, CARRIER_CHECK_DELAY);

	if (suspend_flags & SUSPEND_ALLMODES) {
		/* clear wake-up sources */
		ret = smsc95xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0)
			return ret;

		val &= ~(WUCSR_WAKE_EN_ | WUCSR_MPEN_);

		ret = smsc95xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0)
			return ret;

		/* clear wake-up status */
		ret = smsc95xx_read_reg_nopm(dev, PM_CTRL, &val);
		if (ret < 0)
			return ret;

		val &= ~PM_CTL_WOL_EN_;
		val |= PM_CTL_WUPS_;

		ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
		if (ret < 0)
			return ret;
	}

	ret = usbnet_resume(intf);
	if (ret < 0)
		netdev_warn(dev->net, "usbnet_resume error\n");

	return ret;
}