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
struct mt76_dev {scalar_t__ csa_complete; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  __mt76_csa_finish ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76_dev*) ; 

void mt76_csa_finish(struct mt76_dev *dev)
{
	if (!dev->csa_complete)
		return;

	ieee80211_iterate_active_interfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		__mt76_csa_finish, dev);

	dev->csa_complete = 0;
}