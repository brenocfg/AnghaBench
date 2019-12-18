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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  PCS_UC8051_STATUS_REG ; 
 int PCS_UC_STATUS_FW_SAVE ; 
 int PCS_UC_STATUS_LBN ; 
 int PCS_UC_STATUS_WIDTH ; 
 int /*<<< orphan*/  QT2025C_FWSTART_WAIT ; 
 unsigned long QT2025C_MAX_FWSTART_TIME ; 
 int ef4_mdio_read (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int qt2025c_wait_fw_status_good(struct ef4_nic *efx)
{
	unsigned long timeout = jiffies + QT2025C_MAX_FWSTART_TIME;
	int reg;

	/* Wait for firmware status to look good */
	for (;;) {
		reg = ef4_mdio_read(efx, MDIO_MMD_PCS, PCS_UC8051_STATUS_REG);
		if (reg < 0)
			return reg;
		if ((reg &
		     ((1 << PCS_UC_STATUS_WIDTH) - 1) << PCS_UC_STATUS_LBN) >=
		    PCS_UC_STATUS_FW_SAVE)
			break;
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;
		msleep(QT2025C_FWSTART_WAIT);
	}

	return 0;
}