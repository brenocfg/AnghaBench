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
struct sdio_mmc_card {struct mwifiex_adapter* adapter; } ;
struct sdio_func {int dummy; } ;
struct mwifiex_adapter {int /*<<< orphan*/  work_flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_STA ; 
 int /*<<< orphan*/  MWIFIEX_IS_SUSPENDED ; 
 int /*<<< orphan*/  MWIFIEX_SYNC_CMD ; 
 int /*<<< orphan*/  WARN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  mwifiex_cancel_hs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_disable_wake (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 struct sdio_mmc_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_sdio_resume(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct sdio_mmc_card *card;
	struct mwifiex_adapter *adapter;

	card = sdio_get_drvdata(func);
	if (!card || !card->adapter) {
		dev_err(dev, "resume: invalid card or adapter\n");
		return 0;
	}

	adapter = card->adapter;

	if (!test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) {
		mwifiex_dbg(adapter, WARN,
			    "device already resumed\n");
		return 0;
	}

	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);

	/* Disable Host Sleep */
	mwifiex_cancel_hs(mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA),
			  MWIFIEX_SYNC_CMD);

	mwifiex_disable_wake(adapter);

	return 0;
}