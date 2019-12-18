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
struct vnt_private {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnt_update_pre_ed_threshold (struct vnt_private*,int) ; 

__attribute__((used)) static void vnt_sw_scan_complete(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct vnt_private *priv = hw->priv;

	/* Return sensitivity to channel level*/
	vnt_update_pre_ed_threshold(priv, false);
}