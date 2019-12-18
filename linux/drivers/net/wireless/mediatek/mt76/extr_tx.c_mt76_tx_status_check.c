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
struct sk_buff_head {int dummy; } ;
struct mt76_wcid {int dummy; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_tx_status_lock (struct mt76_dev*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_tx_status_skb_get (struct mt76_dev*,struct mt76_wcid*,int,struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_tx_status_unlock (struct mt76_dev*,struct sk_buff_head*) ; 

void
mt76_tx_status_check(struct mt76_dev *dev, struct mt76_wcid *wcid, bool flush)
{
	struct sk_buff_head list;

	mt76_tx_status_lock(dev, &list);
	mt76_tx_status_skb_get(dev, wcid, flush ? -1 : 0, &list);
	mt76_tx_status_unlock(dev, &list);
}