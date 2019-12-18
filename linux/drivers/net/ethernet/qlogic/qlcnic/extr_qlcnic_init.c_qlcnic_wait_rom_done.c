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
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 long QLCNIC_MAX_ROM_WAIT_USEC ; 
 int /*<<< orphan*/  QLCNIC_ROMUSB_GLB_STATUS ; 
 long QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qlcnic_wait_rom_done(struct qlcnic_adapter *adapter)
{
	long timeout = 0;
	long done = 0;
	int err = 0;

	cond_resched();
	while (done == 0) {
		done = QLCRD32(adapter, QLCNIC_ROMUSB_GLB_STATUS, &err);
		done &= 2;
		if (++timeout >= QLCNIC_MAX_ROM_WAIT_USEC) {
			dev_err(&adapter->pdev->dev,
				"Timeout reached  waiting for rom done");
			return -EIO;
		}
		udelay(1);
	}
	return 0;
}