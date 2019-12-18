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
typedef  int /*<<< orphan*/  u16 ;
struct rtw_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_ASSOCIATE_START ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_coex_connect_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_ops_mgd_prepare_tx(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   u16 duration)
{
	struct rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	rtw_coex_connect_notify(rtwdev, COEX_ASSOCIATE_START);
	mutex_unlock(&rtwdev->mutex);
}