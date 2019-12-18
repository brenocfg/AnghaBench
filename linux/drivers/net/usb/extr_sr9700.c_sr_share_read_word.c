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
struct usbnet {int /*<<< orphan*/  phy_mutex; int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EPAR_PHY_ADR ; 
 int EPCR_EPOS ; 
 int EPCR_ERPRR ; 
 int /*<<< orphan*/  SR_EPAR ; 
 int /*<<< orphan*/  SR_EPCR ; 
 int /*<<< orphan*/  SR_EPDR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int sr_read (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sr_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int wait_phy_eeprom_ready (struct usbnet*,int) ; 

__attribute__((used)) static int sr_share_read_word(struct usbnet *dev, int phy, u8 reg,
			      __le16 *value)
{
	int ret;

	mutex_lock(&dev->phy_mutex);

	sr_write_reg(dev, SR_EPAR, phy ? (reg | EPAR_PHY_ADR) : reg);
	sr_write_reg(dev, SR_EPCR, phy ? (EPCR_EPOS | EPCR_ERPRR) : EPCR_ERPRR);

	ret = wait_phy_eeprom_ready(dev, phy);
	if (ret < 0)
		goto out_unlock;

	sr_write_reg(dev, SR_EPCR, 0x0);
	ret = sr_read(dev, SR_EPDR, 2, value);

	netdev_dbg(dev->net, "read shared %d 0x%02x returned 0x%04x, %d\n",
		   phy, reg, *value, ret);

out_unlock:
	mutex_unlock(&dev->phy_mutex);
	return ret;
}