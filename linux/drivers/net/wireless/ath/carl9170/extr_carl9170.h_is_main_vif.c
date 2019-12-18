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
struct ieee80211_vif {int dummy; } ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline bool is_main_vif(struct ar9170 *ar, struct ieee80211_vif *vif)
{
	bool ret;

	rcu_read_lock();
	ret = (carl9170_get_main_vif(ar) == vif);
	rcu_read_unlock();
	return ret;
}