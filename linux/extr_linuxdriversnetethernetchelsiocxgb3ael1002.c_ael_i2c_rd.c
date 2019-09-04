#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  prtad; } ;
struct cphy {TYPE_1__ mdio; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEL_I2C_CTRL ; 
 int /*<<< orphan*/  AEL_I2C_DATA ; 
 int /*<<< orphan*/  AEL_I2C_STAT ; 
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int t3_mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ael_i2c_rd(struct cphy *phy, int dev_addr, int word_addr)
{
	int i, err;
	unsigned int stat, data;

	err = t3_mdio_write(phy, MDIO_MMD_PMAPMD, AEL_I2C_CTRL,
			    (dev_addr << 8) | (1 << 8) | word_addr);
	if (err)
		return err;

	for (i = 0; i < 200; i++) {
		msleep(1);
		err = t3_mdio_read(phy, MDIO_MMD_PMAPMD, AEL_I2C_STAT, &stat);
		if (err)
			return err;
		if ((stat & 3) == 1) {
			err = t3_mdio_read(phy, MDIO_MMD_PMAPMD, AEL_I2C_DATA,
					   &data);
			if (err)
				return err;
			return data >> 8;
		}
	}
	CH_WARN(phy->adapter, "PHY %u i2c read of dev.addr %#x.%#x timed out\n",
		phy->mdio.prtad, dev_addr, word_addr);
	return -ETIMEDOUT;
}