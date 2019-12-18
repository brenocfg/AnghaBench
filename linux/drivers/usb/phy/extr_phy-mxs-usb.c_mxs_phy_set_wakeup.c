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
struct usb_phy {scalar_t__ io_priv; } ;
struct mxs_phy {int dummy; } ;

/* Variables and functions */
 int BM_USBPHY_CTRL_ENDPDMCHG_WKUP ; 
 int BM_USBPHY_CTRL_ENIDCHG_WKUP ; 
 int BM_USBPHY_CTRL_ENVBUSCHG_WKUP ; 
 scalar_t__ HW_USBPHY_CTRL_CLR ; 
 scalar_t__ HW_USBPHY_CTRL_SET ; 
 int /*<<< orphan*/  mxs_phy_disconnect_line (struct mxs_phy*,int) ; 
 struct mxs_phy* to_mxs_phy (struct usb_phy*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int mxs_phy_set_wakeup(struct usb_phy *x, bool enabled)
{
	struct mxs_phy *mxs_phy = to_mxs_phy(x);
	u32 value = BM_USBPHY_CTRL_ENVBUSCHG_WKUP |
			BM_USBPHY_CTRL_ENDPDMCHG_WKUP |
				BM_USBPHY_CTRL_ENIDCHG_WKUP;
	if (enabled) {
		mxs_phy_disconnect_line(mxs_phy, true);
		writel_relaxed(value, x->io_priv + HW_USBPHY_CTRL_SET);
	} else {
		writel_relaxed(value, x->io_priv + HW_USBPHY_CTRL_CLR);
		mxs_phy_disconnect_line(mxs_phy, false);
	}

	return 0;
}