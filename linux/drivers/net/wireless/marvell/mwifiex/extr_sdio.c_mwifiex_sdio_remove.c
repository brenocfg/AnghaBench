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
typedef  scalar_t__ u16 ;
struct sdio_mmc_card {struct mwifiex_adapter* adapter; int /*<<< orphan*/  fw_done; } ;
struct sdio_func {int /*<<< orphan*/  num; } ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_adapter {int /*<<< orphan*/  mfg_mode; int /*<<< orphan*/  priv_num; } ;

/* Variables and functions */
 scalar_t__ FIRMWARE_READY_SDIO ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 int /*<<< orphan*/  MWIFIEX_FUNC_SHUTDOWN ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_deauthenticate_all (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_disable_auto_ds (struct mwifiex_private*) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_init_shutdown_fw (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_remove_card (struct mwifiex_adapter*) ; 
 int mwifiex_sdio_read_fw_status (struct mwifiex_adapter*,scalar_t__*) ; 
 struct sdio_mmc_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_sdio_remove(struct sdio_func *func)
{
	struct sdio_mmc_card *card;
	struct mwifiex_adapter *adapter;
	struct mwifiex_private *priv;
	int ret = 0;
	u16 firmware_stat;

	card = sdio_get_drvdata(func);
	if (!card)
		return;

	wait_for_completion(&card->fw_done);

	adapter = card->adapter;
	if (!adapter || !adapter->priv_num)
		return;

	mwifiex_dbg(adapter, INFO, "info: SDIO func num=%d\n", func->num);

	ret = mwifiex_sdio_read_fw_status(adapter, &firmware_stat);
	if (!ret && firmware_stat == FIRMWARE_READY_SDIO &&
	    !adapter->mfg_mode) {
		mwifiex_deauthenticate_all(adapter);

		priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
		mwifiex_disable_auto_ds(priv);
		mwifiex_init_shutdown_fw(priv, MWIFIEX_FUNC_SHUTDOWN);
	}

	mwifiex_remove_card(adapter);
}