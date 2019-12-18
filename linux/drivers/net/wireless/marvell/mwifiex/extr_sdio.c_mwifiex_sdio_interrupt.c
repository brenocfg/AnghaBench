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
struct mwifiex_adapter {scalar_t__ ps_state; int /*<<< orphan*/  pps_uapsd_mode; } ;

/* Variables and functions */
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_SLEEP ; 
 int /*<<< orphan*/  mwifiex_interrupt_status (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_main_process (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  pr_err (char*,struct sdio_func*,struct sdio_mmc_card*,struct mwifiex_adapter*) ; 
 struct sdio_mmc_card* sdio_get_drvdata (struct sdio_func*) ; 

__attribute__((used)) static void
mwifiex_sdio_interrupt(struct sdio_func *func)
{
	struct mwifiex_adapter *adapter;
	struct sdio_mmc_card *card;

	card = sdio_get_drvdata(func);
	if (!card || !card->adapter) {
		pr_err("int: func=%p card=%p adapter=%p\n",
		       func, card, card ? card->adapter : NULL);
		return;
	}
	adapter = card->adapter;

	if (!adapter->pps_uapsd_mode && adapter->ps_state == PS_STATE_SLEEP)
		adapter->ps_state = PS_STATE_AWAKE;

	mwifiex_interrupt_status(adapter);
	mwifiex_main_process(adapter);
}