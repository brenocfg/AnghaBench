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
struct smsc75xx_priv {int suspend_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_PHY_PWRUP ; 
 int PMT_CTL_WOL_EN ; 
 int PMT_CTL_WUPS ; 
 int SUSPEND_ALLMODES ; 
 int SUSPEND_SUSPEND2 ; 
 int /*<<< orphan*/  WUCSR ; 
 int WUCSR_BCST_EN ; 
 int WUCSR_MPEN ; 
 int WUCSR_PFDA_EN ; 
 int WUCSR_WUEN ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int smsc75xx_read_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc75xx_wait_ready (struct usbnet*,int) ; 
 int smsc75xx_write_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usbnet_resume (struct usb_interface*) ; 

__attribute__((used)) static int smsc75xx_resume(struct usb_interface *intf)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct smsc75xx_priv *pdata = (struct smsc75xx_priv *)(dev->data[0]);
	u8 suspend_flags = pdata->suspend_flags;
	int ret;
	u32 val;

	netdev_dbg(dev->net, "resume suspend_flags=0x%02x\n", suspend_flags);

	/* do this first to ensure it's cleared even in error case */
	pdata->suspend_flags = 0;

	if (suspend_flags & SUSPEND_ALLMODES) {
		/* Disable wakeup sources */
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			return ret;
		}

		val &= ~(WUCSR_WUEN | WUCSR_MPEN | WUCSR_PFDA_EN
			| WUCSR_BCST_EN);

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			return ret;
		}

		/* clear wake-up status */
		ret = smsc75xx_read_reg_nopm(dev, PMT_CTL, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			return ret;
		}

		val &= ~PMT_CTL_WOL_EN;
		val |= PMT_CTL_WUPS;

		ret = smsc75xx_write_reg_nopm(dev, PMT_CTL, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			return ret;
		}
	}

	if (suspend_flags & SUSPEND_SUSPEND2) {
		netdev_info(dev->net, "resuming from SUSPEND2\n");

		ret = smsc75xx_read_reg_nopm(dev, PMT_CTL, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			return ret;
		}

		val |= PMT_CTL_PHY_PWRUP;

		ret = smsc75xx_write_reg_nopm(dev, PMT_CTL, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			return ret;
		}
	}

	ret = smsc75xx_wait_ready(dev, 1);
	if (ret < 0) {
		netdev_warn(dev->net, "device not ready in smsc75xx_resume\n");
		return ret;
	}

	return usbnet_resume(intf);
}