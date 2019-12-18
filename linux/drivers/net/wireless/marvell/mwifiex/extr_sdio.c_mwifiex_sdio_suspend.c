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
struct sdio_mmc_card {struct mwifiex_adapter* adapter; int /*<<< orphan*/  fw_done; } ;
struct sdio_func {int dummy; } ;
struct mwifiex_adapter {int /*<<< orphan*/  work_flags; } ;
struct device {int dummy; } ;
typedef  int mmc_pm_flag_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSYS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INFO ; 
 int MMC_PM_KEEP_POWER ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_ENABLING ; 
 int /*<<< orphan*/  MWIFIEX_IS_SUSPENDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_disable_wake (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_enable_hs (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_enable_wake (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 
 struct sdio_mmc_card* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_get_host_pm_caps (struct sdio_func*) ; 
 int sdio_set_host_pm_flags (struct sdio_func*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_sdio_suspend(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct sdio_mmc_card *card;
	struct mwifiex_adapter *adapter;
	mmc_pm_flag_t pm_flag = 0;
	int ret = 0;

	pm_flag = sdio_get_host_pm_caps(func);
	pr_debug("cmd: %s: suspend: PM flag = 0x%x\n",
		 sdio_func_id(func), pm_flag);
	if (!(pm_flag & MMC_PM_KEEP_POWER)) {
		dev_err(dev, "%s: cannot remain alive while host is"
			" suspended\n", sdio_func_id(func));
		return -ENOSYS;
	}

	card = sdio_get_drvdata(func);
	if (!card) {
		dev_err(dev, "suspend: invalid card\n");
		return 0;
	}

	/* Might still be loading firmware */
	wait_for_completion(&card->fw_done);

	adapter = card->adapter;
	if (!adapter) {
		dev_err(dev, "adapter is not valid\n");
		return 0;
	}

	mwifiex_enable_wake(adapter);

	/* Enable the Host Sleep */
	if (!mwifiex_enable_hs(adapter)) {
		mwifiex_dbg(adapter, ERROR,
			    "cmd: failed to suspend\n");
		clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
		mwifiex_disable_wake(adapter);
		return -EFAULT;
	}

	mwifiex_dbg(adapter, INFO,
		    "cmd: suspend with MMC_PM_KEEP_POWER\n");
	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);

	/* Indicate device suspended */
	set_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);

	return ret;
}