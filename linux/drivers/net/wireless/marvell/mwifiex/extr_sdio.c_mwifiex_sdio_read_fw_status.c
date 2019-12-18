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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sdio_mmc_card {struct mwifiex_sdio_card_reg* reg; } ;
struct mwifiex_sdio_card_reg {int /*<<< orphan*/  status_reg_1; int /*<<< orphan*/  status_reg_0; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;

/* Variables and functions */
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mwifiex_sdio_read_fw_status(struct mwifiex_adapter *adapter, u16 *dat)
{
	struct sdio_mmc_card *card = adapter->card;
	const struct mwifiex_sdio_card_reg *reg = card->reg;
	u8 fws0, fws1;

	if (mwifiex_read_reg(adapter, reg->status_reg_0, &fws0))
		return -1;

	if (mwifiex_read_reg(adapter, reg->status_reg_1, &fws1))
		return -1;

	*dat = (u16)((fws1 << 8) | fws0);
	return 0;
}