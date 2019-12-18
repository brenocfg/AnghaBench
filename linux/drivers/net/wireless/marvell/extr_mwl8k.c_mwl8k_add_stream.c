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
typedef  int /*<<< orphan*/  u8 ;
struct mwl8k_priv {struct mwl8k_ampdu_stream* ampdu; } ;
struct mwl8k_ampdu_stream {scalar_t__ state; int idx; int /*<<< orphan*/  tid; struct ieee80211_sta* sta; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mwl8k_priv* priv; } ;

/* Variables and functions */
 scalar_t__ AMPDU_NO_STREAM ; 
 scalar_t__ AMPDU_STREAM_NEW ; 
 int MWL8K_NUM_AMPDU_STREAMS ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mwl8k_ampdu_stream *
mwl8k_add_stream(struct ieee80211_hw *hw, struct ieee80211_sta *sta, u8 tid)
{
	struct mwl8k_ampdu_stream *stream;
	struct mwl8k_priv *priv = hw->priv;
	int i;

	for (i = 0; i < MWL8K_NUM_AMPDU_STREAMS; i++) {
		stream = &priv->ampdu[i];
		if (stream->state == AMPDU_NO_STREAM) {
			stream->sta = sta;
			stream->state = AMPDU_STREAM_NEW;
			stream->tid = tid;
			stream->idx = i;
			wiphy_debug(hw->wiphy, "Added a new stream for %pM %d",
				    sta->addr, tid);
			return stream;
		}
	}
	return NULL;
}