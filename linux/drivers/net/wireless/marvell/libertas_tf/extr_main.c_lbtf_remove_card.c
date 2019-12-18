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
struct lbtf_private {int surpriseremoved; struct ieee80211_hw* hw; int /*<<< orphan*/  command_timer; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_MAIN ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_free_adapter (struct lbtf_private*) ; 

int lbtf_remove_card(struct lbtf_private *priv)
{
	struct ieee80211_hw *hw = priv->hw;

	lbtf_deb_enter(LBTF_DEB_MAIN);

	priv->surpriseremoved = 1;
	del_timer(&priv->command_timer);
	lbtf_free_adapter(priv);
	priv->hw = NULL;
	ieee80211_unregister_hw(hw);
	ieee80211_free_hw(hw);

	lbtf_deb_leave(LBTF_DEB_MAIN);
	return 0;
}