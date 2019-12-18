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
typedef  int /*<<< orphan*/  u32 ;
struct lbtf_private {scalar_t__ cur_freq; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct lbtf_private* priv; } ;
struct TYPE_3__ {scalar_t__ center_freq; int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_MACOPS ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_set_channel (struct lbtf_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbtf_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct lbtf_private *priv = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;
	lbtf_deb_enter(LBTF_DEB_MACOPS);

	if (conf->chandef.chan->center_freq != priv->cur_freq) {
		priv->cur_freq = conf->chandef.chan->center_freq;
		lbtf_set_channel(priv, conf->chandef.chan->hw_value);
	}
	lbtf_deb_leave(LBTF_DEB_MACOPS);
	return 0;
}