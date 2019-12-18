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
struct usbnet {int /*<<< orphan*/  phy_mutex; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EPAR_PHY_ADR ; 
 int EPCR_EPOS ; 
 int EPCR_ERPRW ; 
 int EPCR_WEP ; 
 int /*<<< orphan*/  SR_EPAR ; 
 int /*<<< orphan*/  SR_EPCR ; 
 int /*<<< orphan*/  SR_EPDR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sr_write (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sr_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int wait_phy_eeprom_ready (struct usbnet*,int) ; 

__attribute__((used)) static int sr_share_write_word(struct usbnet *dev, int phy, u8 reg,
			       __le16 value)
{
	int ret;

	mutex_lock(&dev->phy_mutex);

	ret = sr_write(dev, SR_EPDR, 2, &value);
	if (ret < 0)
		goto out_unlock;

	sr_write_reg(dev, SR_EPAR, phy ? (reg | EPAR_PHY_ADR) : reg);
	sr_write_reg(dev, SR_EPCR, phy ? (EPCR_WEP | EPCR_EPOS | EPCR_ERPRW) :
		    (EPCR_WEP | EPCR_ERPRW));

	ret = wait_phy_eeprom_ready(dev, phy);
	if (ret < 0)
		goto out_unlock;

	sr_write_reg(dev, SR_EPCR, 0x0);

out_unlock:
	mutex_unlock(&dev->phy_mutex);
	return ret;
}