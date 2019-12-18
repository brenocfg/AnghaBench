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
struct sdio_mmc_card {int dummy; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_RX_AGGR_BUF_RESET (struct sdio_mmc_card*) ; 
 int /*<<< orphan*/  MP_TX_AGGR_BUF_RESET (struct sdio_mmc_card*) ; 

__attribute__((used)) static void mwifiex_cleanup_mpa_buf(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;

	MP_TX_AGGR_BUF_RESET(card);
	MP_RX_AGGR_BUF_RESET(card);
}