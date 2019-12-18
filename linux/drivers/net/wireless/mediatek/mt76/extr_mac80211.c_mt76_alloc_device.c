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
struct mt76_driver_ops {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  status_list; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cc_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_lock; struct mt76_driver_ops const* drv; struct device* dev; struct ieee80211_hw* hw; } ;
struct ieee80211_ops {int dummy; } ;
struct ieee80211_hw {struct mt76_dev* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ieee80211_hw* ieee80211_alloc_hw (unsigned int,struct ieee80211_ops const*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_tx_tasklet ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

struct mt76_dev *
mt76_alloc_device(struct device *pdev, unsigned int size,
		  const struct ieee80211_ops *ops,
		  const struct mt76_driver_ops *drv_ops)
{
	struct ieee80211_hw *hw;
	struct mt76_dev *dev;

	hw = ieee80211_alloc_hw(size, ops);
	if (!hw)
		return NULL;

	dev = hw->priv;
	dev->hw = hw;
	dev->dev = pdev;
	dev->drv = drv_ops;

	spin_lock_init(&dev->rx_lock);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->cc_lock);
	mutex_init(&dev->mutex);
	init_waitqueue_head(&dev->tx_wait);
	skb_queue_head_init(&dev->status_list);

	tasklet_init(&dev->tx_tasklet, mt76_tx_tasklet, (unsigned long)dev);

	return dev;
}