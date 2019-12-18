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
typedef  size_t u8 ;
struct mt76_wcid {int /*<<< orphan*/ * aggr; } ;
struct mt76_rx_tid {int dummy; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct mt76_rx_tid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rx_aggr_shutdown (struct mt76_dev*,struct mt76_rx_tid*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mt76_rx_tid* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void mt76_rx_aggr_stop(struct mt76_dev *dev, struct mt76_wcid *wcid, u8 tidno)
{
	struct mt76_rx_tid *tid;

	rcu_read_lock();

	tid = rcu_dereference(wcid->aggr[tidno]);
	if (tid) {
		rcu_assign_pointer(wcid->aggr[tidno], NULL);
		mt76_rx_aggr_shutdown(dev, tid);
		kfree_rcu(tid, rcu_head);
	}

	rcu_read_unlock();
}