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
typedef  int u32 ;
struct tb_nhi {scalar_t__ iobase; TYPE_1__* pdev; } ;
struct tb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ REG_FW_STS ; 
 int REG_FW_STS_ICM_EN ; 
 int REG_FW_STS_NVM_AUTH_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int icm_firmware_reset (struct tb*,struct tb_nhi*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int icm_firmware_start(struct tb *tb, struct tb_nhi *nhi)
{
	unsigned int retries = 10;
	int ret;
	u32 val;

	/* Check if the ICM firmware is already running */
	val = ioread32(nhi->iobase + REG_FW_STS);
	if (val & REG_FW_STS_ICM_EN)
		return 0;

	dev_dbg(&nhi->pdev->dev, "starting ICM firmware\n");

	ret = icm_firmware_reset(tb, nhi);
	if (ret)
		return ret;

	/* Wait until the ICM firmware tells us it is up and running */
	do {
		/* Check that the ICM firmware is running */
		val = ioread32(nhi->iobase + REG_FW_STS);
		if (val & REG_FW_STS_NVM_AUTH_DONE)
			return 0;

		msleep(300);
	} while (--retries);

	return -ETIMEDOUT;
}