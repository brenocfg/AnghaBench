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
typedef  int /*<<< orphan*/  u8 ;
struct qcom_usb_hs_phy {int /*<<< orphan*/  ulpi; int /*<<< orphan*/  vbus_edev; } ;
struct phy {int dummy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_MODE_USB_DEVICE 130 
#define  PHY_MODE_USB_HOST 129 
#define  PHY_MODE_USB_OTG 128 
 int /*<<< orphan*/  ULPI_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULPI_INT_IDGRD ; 
 int /*<<< orphan*/  ULPI_INT_SESS_VALID ; 
 int /*<<< orphan*/  ULPI_MISC_A ; 
 int /*<<< orphan*/  ULPI_MISC_A_VBUSVLDEXTSEL ; 
 int /*<<< orphan*/  ULPI_PWR_CLK_MNG_REG ; 
 int /*<<< orphan*/  ULPI_PWR_OTG_COMP_DISABLE ; 
 int /*<<< orphan*/  ULPI_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULPI_USB_INT_EN_FALL ; 
 int /*<<< orphan*/  ULPI_USB_INT_EN_RISE ; 
 struct qcom_usb_hs_phy* phy_get_drvdata (struct phy*) ; 
 int ulpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_usb_hs_phy_set_mode(struct phy *phy,
				    enum phy_mode mode, int submode)
{
	struct qcom_usb_hs_phy *uphy = phy_get_drvdata(phy);
	u8 addr;
	int ret;

	if (!uphy->vbus_edev) {
		u8 val = 0;

		switch (mode) {
		case PHY_MODE_USB_OTG:
		case PHY_MODE_USB_HOST:
			val |= ULPI_INT_IDGRD;
			/* fall through */
		case PHY_MODE_USB_DEVICE:
			val |= ULPI_INT_SESS_VALID;
		default:
			break;
		}

		ret = ulpi_write(uphy->ulpi, ULPI_USB_INT_EN_RISE, val);
		if (ret)
			return ret;
		ret = ulpi_write(uphy->ulpi, ULPI_USB_INT_EN_FALL, val);
	} else {
		switch (mode) {
		case PHY_MODE_USB_OTG:
		case PHY_MODE_USB_DEVICE:
			addr = ULPI_SET(ULPI_MISC_A);
			break;
		case PHY_MODE_USB_HOST:
			addr = ULPI_CLR(ULPI_MISC_A);
			break;
		default:
			return -EINVAL;
		}

		ret = ulpi_write(uphy->ulpi, ULPI_SET(ULPI_PWR_CLK_MNG_REG),
				 ULPI_PWR_OTG_COMP_DISABLE);
		if (ret)
			return ret;
		ret = ulpi_write(uphy->ulpi, addr, ULPI_MISC_A_VBUSVLDEXTSEL);
	}

	return ret;
}