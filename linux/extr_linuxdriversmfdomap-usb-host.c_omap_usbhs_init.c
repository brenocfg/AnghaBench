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
struct usbhs_hcd_omap {int usbhs_rev; int /*<<< orphan*/  uhh_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int OMAP4_UHH_HOSTCONFIG_APP_START_CLK ; 
 int /*<<< orphan*/  OMAP_UHH_HOSTCONFIG ; 
 unsigned int OMAP_UHH_HOSTCONFIG_INCR16_BURST_EN ; 
 unsigned int OMAP_UHH_HOSTCONFIG_INCR4_BURST_EN ; 
 unsigned int OMAP_UHH_HOSTCONFIG_INCR8_BURST_EN ; 
 unsigned int OMAP_UHH_HOSTCONFIG_INCRX_ALIGN_EN ; 
#define  OMAP_USBHS_REV1 129 
#define  OMAP_USBHS_REV2 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct usbhs_hcd_omap* dev_get_drvdata (struct device*) ; 
 unsigned int omap_usbhs_rev1_hostconfig (struct usbhs_hcd_omap*,unsigned int) ; 
 unsigned int omap_usbhs_rev2_hostconfig (struct usbhs_hcd_omap*,unsigned int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 unsigned int usbhs_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void omap_usbhs_init(struct device *dev)
{
	struct usbhs_hcd_omap		*omap = dev_get_drvdata(dev);
	unsigned			reg;

	dev_dbg(dev, "starting TI HSUSB Controller\n");

	pm_runtime_get_sync(dev);

	reg = usbhs_read(omap->uhh_base, OMAP_UHH_HOSTCONFIG);
	/* setup ULPI bypass and burst configurations */
	reg |= (OMAP_UHH_HOSTCONFIG_INCR4_BURST_EN
			| OMAP_UHH_HOSTCONFIG_INCR8_BURST_EN
			| OMAP_UHH_HOSTCONFIG_INCR16_BURST_EN);
	reg |= OMAP4_UHH_HOSTCONFIG_APP_START_CLK;
	reg &= ~OMAP_UHH_HOSTCONFIG_INCRX_ALIGN_EN;

	switch (omap->usbhs_rev) {
	case OMAP_USBHS_REV1:
		reg = omap_usbhs_rev1_hostconfig(omap, reg);
		break;

	case OMAP_USBHS_REV2:
		reg = omap_usbhs_rev2_hostconfig(omap, reg);
		break;

	default:	/* newer revisions */
		reg = omap_usbhs_rev2_hostconfig(omap, reg);
		break;
	}

	usbhs_write(omap->uhh_base, OMAP_UHH_HOSTCONFIG, reg);
	dev_dbg(dev, "UHH setup done, uhh_hostconfig=%x\n", reg);

	pm_runtime_put_sync(dev);
}