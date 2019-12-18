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
struct vnt_private {struct ieee80211_hw* hw; } ;
struct ieee80211_conf {int listen_interval; } ;
struct ieee80211_hw {struct ieee80211_conf conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_REG_PSCTL ; 
 int /*<<< orphan*/  PSCTL_LNBCN ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_on (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vnt_next_tbtt_wakeup(struct vnt_private *priv)
{
	struct ieee80211_hw *hw = priv->hw;
	struct ieee80211_conf *conf = &hw->conf;
	int wake_up = false;

	if (conf->listen_interval > 1) {
		/* Turn on wake up to listen next beacon */
		vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_LNBCN);
		wake_up = true;
	}

	return wake_up;
}