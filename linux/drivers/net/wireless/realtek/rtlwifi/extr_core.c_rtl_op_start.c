#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  watchdog_timer; } ;
struct rtl_priv {TYPE_3__ locks; TYPE_2__ works; TYPE_1__* intf_ops; int /*<<< orphan*/  status; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int (* adapter_start ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTL_STATUS_INTERFACE_START ; 
 int /*<<< orphan*/  is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_watch_dog_timer_callback (int /*<<< orphan*/ *) ; 
 int stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtl_op_start(struct ieee80211_hw *hw)
{
	int err = 0;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (!is_hal_stop(rtlhal))
		return 0;
	if (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		return 0;
	mutex_lock(&rtlpriv->locks.conf_mutex);
	err = rtlpriv->intf_ops->adapter_start(hw);
	if (!err)
		rtl_watch_dog_timer_callback(&rtlpriv->works.watchdog_timer);
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	return err;
}