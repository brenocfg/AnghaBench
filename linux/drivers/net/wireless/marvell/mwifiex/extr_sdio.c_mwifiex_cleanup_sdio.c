#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  len_arr; int /*<<< orphan*/  skb_arr; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct sdio_mmc_card {TYPE_2__ mpa_rx; TYPE_1__ mpa_tx; int /*<<< orphan*/  mp_regs; int /*<<< orphan*/  work; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_cleanup_sdio(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;

	cancel_work_sync(&card->work);

	kfree(card->mp_regs);
	kfree(card->mpa_rx.skb_arr);
	kfree(card->mpa_rx.len_arr);
	kfree(card->mpa_tx.buf);
	kfree(card->mpa_rx.buf);
}