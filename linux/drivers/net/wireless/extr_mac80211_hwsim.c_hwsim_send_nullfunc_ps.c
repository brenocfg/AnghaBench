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
struct mac80211_hwsim_data {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsim_send_nullfunc (struct mac80211_hwsim_data*,int /*<<< orphan*/ *,struct ieee80211_vif*,int) ; 

__attribute__((used)) static void hwsim_send_nullfunc_ps(void *dat, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct mac80211_hwsim_data *data = dat;
	hwsim_send_nullfunc(data, mac, vif, 1);
}