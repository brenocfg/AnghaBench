#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct cdns3 {int /*<<< orphan*/  dev; TYPE_2__* otg_v0_regs; TYPE_1__* otg_v1_regs; int /*<<< orphan*/  version; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl1; } ;
struct TYPE_3__ {int /*<<< orphan*/  override; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS3_CONTROLLER_V1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  OVERRIDE_IDPULLUP ; 
 int /*<<< orphan*/  OVERRIDE_IDPULLUP_V0 ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cdns3_set_mode(struct cdns3 *cdns, enum usb_dr_mode mode)
{
	int ret = 0;
	u32 reg;

	switch (mode) {
	case USB_DR_MODE_PERIPHERAL:
		break;
	case USB_DR_MODE_HOST:
		break;
	case USB_DR_MODE_OTG:
		dev_dbg(cdns->dev, "Set controller to OTG mode\n");
		if (cdns->version == CDNS3_CONTROLLER_V1) {
			reg = readl(&cdns->otg_v1_regs->override);
			reg |= OVERRIDE_IDPULLUP;
			writel(reg, &cdns->otg_v1_regs->override);
		} else {
			reg = readl(&cdns->otg_v0_regs->ctrl1);
			reg |= OVERRIDE_IDPULLUP_V0;
			writel(reg, &cdns->otg_v0_regs->ctrl1);
		}

		/*
		 * Hardware specification says: "ID_VALUE must be valid within
		 * 50ms after idpullup is set to '1" so driver must wait
		 * 50ms before reading this pin.
		 */
		usleep_range(50000, 60000);
		break;
	default:
		dev_err(cdns->dev, "Unsupported mode of operation %d\n", mode);
		return -EINVAL;
	}

	return ret;
}