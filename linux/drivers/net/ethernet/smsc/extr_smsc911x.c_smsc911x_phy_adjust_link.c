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
struct smsc911x_data {scalar_t__ last_duplex; int last_carrier; int gpio_orig_setting; int gpio_setting; int /*<<< orphan*/  using_extphy; int /*<<< orphan*/  mac_lock; } ;
struct phy_device {scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CFG ; 
 int GPIO_CFG_GPIOBUF0_ ; 
 int GPIO_CFG_GPIOD0_ ; 
 int GPIO_CFG_GPIODIR0_ ; 
 int GPIO_CFG_LED1_EN_ ; 
 int /*<<< orphan*/  MAC_CR ; 
 unsigned int MAC_CR_FDPX_ ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 unsigned int smsc911x_mac_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_phy_update_flowcontrol (struct smsc911x_data*) ; 
 int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void smsc911x_phy_adjust_link(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	struct phy_device *phy_dev = dev->phydev;
	unsigned long flags;
	int carrier;

	if (phy_dev->duplex != pdata->last_duplex) {
		unsigned int mac_cr;
		SMSC_TRACE(pdata, hw, "duplex state has changed");

		spin_lock_irqsave(&pdata->mac_lock, flags);
		mac_cr = smsc911x_mac_read(pdata, MAC_CR);
		if (phy_dev->duplex) {
			SMSC_TRACE(pdata, hw,
				   "configuring for full duplex mode");
			mac_cr |= MAC_CR_FDPX_;
		} else {
			SMSC_TRACE(pdata, hw,
				   "configuring for half duplex mode");
			mac_cr &= ~MAC_CR_FDPX_;
		}
		smsc911x_mac_write(pdata, MAC_CR, mac_cr);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);

		smsc911x_phy_update_flowcontrol(pdata);
		pdata->last_duplex = phy_dev->duplex;
	}

	carrier = netif_carrier_ok(dev);
	if (carrier != pdata->last_carrier) {
		SMSC_TRACE(pdata, hw, "carrier state has changed");
		if (carrier) {
			SMSC_TRACE(pdata, hw, "configuring for carrier OK");
			if ((pdata->gpio_orig_setting & GPIO_CFG_LED1_EN_) &&
			    (!pdata->using_extphy)) {
				/* Restore original GPIO configuration */
				pdata->gpio_setting = pdata->gpio_orig_setting;
				smsc911x_reg_write(pdata, GPIO_CFG,
					pdata->gpio_setting);
			}
		} else {
			SMSC_TRACE(pdata, hw, "configuring for no carrier");
			/* Check global setting that LED1
			 * usage is 10/100 indicator */
			pdata->gpio_setting = smsc911x_reg_read(pdata,
				GPIO_CFG);
			if ((pdata->gpio_setting & GPIO_CFG_LED1_EN_) &&
			    (!pdata->using_extphy)) {
				/* Force 10/100 LED off, after saving
				 * original GPIO configuration */
				pdata->gpio_orig_setting = pdata->gpio_setting;

				pdata->gpio_setting &= ~GPIO_CFG_LED1_EN_;
				pdata->gpio_setting |= (GPIO_CFG_GPIOBUF0_
							| GPIO_CFG_GPIODIR0_
							| GPIO_CFG_GPIOD0_);
				smsc911x_reg_write(pdata, GPIO_CFG,
					pdata->gpio_setting);
			}
		}
		pdata->last_carrier = carrier;
	}
}