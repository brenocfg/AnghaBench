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
typedef  int u32 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int*) ; 
 int QLC_83XX_FLASH_READ_RETRY_COUNT ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_STATUS ; 
 int QLC_83XX_FLASH_STATUS_READY ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qlcnic_83xx_poll_flash_status_reg(struct qlcnic_adapter *adapter)
{
	u32 status;
	int retries = QLC_83XX_FLASH_READ_RETRY_COUNT;
	int err = 0;

	do {
		status = QLCRD32(adapter, QLC_83XX_FLASH_STATUS, &err);
		if (err == -EIO)
			return err;

		if ((status & QLC_83XX_FLASH_STATUS_READY) ==
		    QLC_83XX_FLASH_STATUS_READY)
			break;

		usleep_range(1000, 1100);
	} while (--retries);

	if (!retries)
		return -EIO;

	return 0;
}