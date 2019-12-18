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
typedef  int /*<<< orphan*/  u32 ;
struct phy {int dummy; } ;
struct da8xx_usb_phy {int /*<<< orphan*/  regmap; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 int /*<<< orphan*/  CFGCHIP2_OTGMODE_FORCE_DEVICE ; 
 int /*<<< orphan*/  CFGCHIP2_OTGMODE_FORCE_HOST ; 
 int /*<<< orphan*/  CFGCHIP2_OTGMODE_MASK ; 
 int /*<<< orphan*/  CFGCHIP2_OTGMODE_NO_OVERRIDE ; 
 int EINVAL ; 
#define  PHY_MODE_USB_DEVICE 130 
#define  PHY_MODE_USB_HOST 129 
#define  PHY_MODE_USB_OTG 128 
 struct da8xx_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_usb20_phy_set_mode(struct phy *phy,
				    enum phy_mode mode, int submode)
{
	struct da8xx_usb_phy *d_phy = phy_get_drvdata(phy);
	u32 val;

	switch (mode) {
	case PHY_MODE_USB_HOST:		/* Force VBUS valid, ID = 0 */
		val = CFGCHIP2_OTGMODE_FORCE_HOST;
		break;
	case PHY_MODE_USB_DEVICE:	/* Force VBUS valid, ID = 1 */
		val = CFGCHIP2_OTGMODE_FORCE_DEVICE;
		break;
	case PHY_MODE_USB_OTG:	/* Don't override the VBUS/ID comparators */
		val = CFGCHIP2_OTGMODE_NO_OVERRIDE;
		break;
	default:
		return -EINVAL;
	}

	regmap_write_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_OTGMODE_MASK,
			  val);

	return 0;
}