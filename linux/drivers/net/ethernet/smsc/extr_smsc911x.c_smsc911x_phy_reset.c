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
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PMT_CTRL ; 
 unsigned int PMT_CTRL_PHY_RST_ ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int smsc911x_phy_reset(struct smsc911x_data *pdata)
{
	unsigned int temp;
	unsigned int i = 100000;

	temp = smsc911x_reg_read(pdata, PMT_CTRL);
	smsc911x_reg_write(pdata, PMT_CTRL, temp | PMT_CTRL_PHY_RST_);
	do {
		msleep(1);
		temp = smsc911x_reg_read(pdata, PMT_CTRL);
	} while ((i--) && (temp & PMT_CTRL_PHY_RST_));

	if (unlikely(temp & PMT_CTRL_PHY_RST_)) {
		SMSC_WARN(pdata, hw, "PHY reset failed to complete");
		return -EIO;
	}
	/* Extra delay required because the phy may not be completed with
	* its reset when BMCR_RESET is cleared. Specs say 256 uS is
	* enough delay but using 1ms here to be safe */
	msleep(1);

	return 0;
}