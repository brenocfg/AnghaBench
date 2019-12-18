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
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {scalar_t__ iface_down; } ;
struct TYPE_3__ {struct ieee80211_channel* chan; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct ieee80211_vif {TYPE_2__ bss_conf; } ;
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ZONE ; 
 int /*<<< orphan*/  rsi_band_check (struct rsi_common*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_set_channel (struct rsi_common*,struct ieee80211_channel*) ; 

__attribute__((used)) static void rsi_switch_channel(struct rsi_hw *adapter,
			       struct ieee80211_vif *vif)
{
	struct rsi_common *common = adapter->priv;
	struct ieee80211_channel *channel;

	if (common->iface_down)
		return;
	if (!vif)
		return;

	channel = vif->bss_conf.chandef.chan;

	if (!channel)
		return;

	rsi_band_check(common, channel);
	rsi_set_channel(common, channel);
	rsi_dbg(INFO_ZONE, "Switched to channel - %d\n", channel->hw_value);
}