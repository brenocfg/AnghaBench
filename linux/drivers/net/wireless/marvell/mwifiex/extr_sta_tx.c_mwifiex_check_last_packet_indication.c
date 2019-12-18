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
typedef  int u8 ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  period; } ;
struct mwifiex_adapter {int delay_null_pkt; int /*<<< orphan*/  curr_cmd; int /*<<< orphan*/  cmd_sent; TYPE_1__ sleep_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_command_pending (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_wmm_lists_empty (struct mwifiex_adapter*) ; 

u8
mwifiex_check_last_packet_indication(struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	u8 ret = false;

	if (!adapter->sleep_period.period)
		return ret;
	if (mwifiex_wmm_lists_empty(adapter))
			ret = true;

	if (ret && !adapter->cmd_sent && !adapter->curr_cmd &&
	    !is_command_pending(adapter)) {
		adapter->delay_null_pkt = false;
		ret = true;
	} else {
		ret = false;
		adapter->delay_null_pkt = true;
	}
	return ret;
}