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
struct mt76_wcid {int /*<<< orphan*/  rssi; int /*<<< orphan*/  inactive_count; } ;
struct mt76_dev {unsigned long* wcid_mask; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/ * wcid; } ;
typedef  int s8 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int BITS_PER_LONG ; 
 int ewma_signal_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct mt76_wcid* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mt76_get_min_avg_rssi(struct mt76_dev *dev)
{
	struct mt76_wcid *wcid;
	int i, j, min_rssi = 0;
	s8 cur_rssi;

	local_bh_disable();
	rcu_read_lock();

	for (i = 0; i < ARRAY_SIZE(dev->wcid_mask); i++) {
		unsigned long mask = dev->wcid_mask[i];

		if (!mask)
			continue;

		for (j = i * BITS_PER_LONG; mask; j++, mask >>= 1) {
			if (!(mask & 1))
				continue;

			wcid = rcu_dereference(dev->wcid[j]);
			if (!wcid)
				continue;

			spin_lock(&dev->rx_lock);
			if (wcid->inactive_count++ < 5)
				cur_rssi = -ewma_signal_read(&wcid->rssi);
			else
				cur_rssi = 0;
			spin_unlock(&dev->rx_lock);

			if (cur_rssi < min_rssi)
				min_rssi = cur_rssi;
		}
	}

	rcu_read_unlock();
	local_bh_enable();

	return min_rssi;
}