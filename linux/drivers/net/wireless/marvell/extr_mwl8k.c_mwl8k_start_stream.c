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
struct mwl8k_ampdu_stream {scalar_t__ state; int /*<<< orphan*/  tid; TYPE_1__* sta; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ AMPDU_STREAM_NEW ; 
 int ieee80211_start_tx_ba_session (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
mwl8k_start_stream(struct ieee80211_hw *hw, struct mwl8k_ampdu_stream *stream)
{
	int ret;

	/* if the stream has already been started, don't start it again */
	if (stream->state != AMPDU_STREAM_NEW)
		return 0;
	ret = ieee80211_start_tx_ba_session(stream->sta, stream->tid, 0);
	if (ret)
		wiphy_debug(hw->wiphy, "Failed to start stream for %pM %d: "
			    "%d\n", stream->sta->addr, stream->tid, ret);
	else
		wiphy_debug(hw->wiphy, "Started stream for %pM %d\n",
			    stream->sta->addr, stream->tid);
	return ret;
}