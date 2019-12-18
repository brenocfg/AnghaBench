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
struct mwifiex_adapter {scalar_t__ curr_cmd; int /*<<< orphan*/  tx_hw_pending; scalar_t__ cmd_sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 scalar_t__ IS_CARD_RX_RCVD (struct mwifiex_adapter*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  mwifiex_dnld_sleep_confirm_cmd (struct mwifiex_adapter*) ; 

void
mwifiex_check_ps_cond(struct mwifiex_adapter *adapter)
{
	if (!adapter->cmd_sent && !atomic_read(&adapter->tx_hw_pending) &&
	    !adapter->curr_cmd && !IS_CARD_RX_RCVD(adapter))
		mwifiex_dnld_sleep_confirm_cmd(adapter);
	else
		mwifiex_dbg(adapter, CMD,
			    "cmd: Delay Sleep Confirm (%s%s%s%s)\n",
			    (adapter->cmd_sent) ? "D" : "",
			    atomic_read(&adapter->tx_hw_pending) ? "T" : "",
			    (adapter->curr_cmd) ? "C" : "",
			    (IS_CARD_RX_RCVD(adapter)) ? "R" : "");
}