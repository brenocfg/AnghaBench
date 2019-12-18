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
struct smsc911x_data {int generation; int idrev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int HW_CFG ; 
 unsigned int HW_CFG_SRST_ ; 
 int LAN9250 ; 
 unsigned int RESET_CTL ; 
 unsigned int RESET_CTL_DIGITAL_RST_ ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drv ; 
 int smsc911x_phy_disable_energy_detect (struct smsc911x_data*) ; 
 int smsc911x_phy_enable_energy_detect (struct smsc911x_data*) ; 
 int smsc911x_phy_general_power_up (struct smsc911x_data*) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int smsc911x_soft_reset(struct smsc911x_data *pdata)
{
	unsigned int timeout;
	unsigned int temp;
	int ret;
	unsigned int reset_offset = HW_CFG;
	unsigned int reset_mask = HW_CFG_SRST_;

	/*
	 * Make sure to power-up the PHY chip before doing a reset, otherwise
	 * the reset fails.
	 */
	ret = smsc911x_phy_general_power_up(pdata);
	if (ret) {
		SMSC_WARN(pdata, drv, "Failed to power-up the PHY chip");
		return ret;
	}

	/*
	 * LAN9210/LAN9211/LAN9220/LAN9221 chips have an internal PHY that
	 * are initialized in a Energy Detect Power-Down mode that prevents
	 * the MAC chip to be software reseted. So we have to wakeup the PHY
	 * before.
	 */
	if (pdata->generation == 4) {
		ret = smsc911x_phy_disable_energy_detect(pdata);

		if (ret) {
			SMSC_WARN(pdata, drv, "Failed to wakeup the PHY chip");
			return ret;
		}
	}

	if ((pdata->idrev & 0xFFFF0000) == LAN9250) {
		/* special reset for  LAN9250 */
		reset_offset = RESET_CTL;
		reset_mask = RESET_CTL_DIGITAL_RST_;
	}

	/* Reset the LAN911x */
	smsc911x_reg_write(pdata, reset_offset, reset_mask);

	/* verify reset bit is cleared */
	timeout = 10;
	do {
		udelay(10);
		temp = smsc911x_reg_read(pdata, reset_offset);
	} while ((--timeout) && (temp & reset_mask));

	if (unlikely(temp & reset_mask)) {
		SMSC_WARN(pdata, drv, "Failed to complete reset");
		return -EIO;
	}

	if (pdata->generation == 4) {
		ret = smsc911x_phy_enable_energy_detect(pdata);

		if (ret) {
			SMSC_WARN(pdata, drv, "Failed to wakeup the PHY chip");
			return ret;
		}
	}

	return 0;
}