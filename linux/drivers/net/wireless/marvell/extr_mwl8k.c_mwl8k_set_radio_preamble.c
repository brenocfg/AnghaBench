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
struct mwl8k_priv {int radio_short_preamble; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int mwl8k_cmd_radio_control (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static int
mwl8k_set_radio_preamble(struct ieee80211_hw *hw, bool short_preamble)
{
	struct mwl8k_priv *priv = hw->priv;

	priv->radio_short_preamble = short_preamble;

	return mwl8k_cmd_radio_control(hw, 1, 1);
}