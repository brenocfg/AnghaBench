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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ mcu; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dma_idx; TYPE_2__ mmio; } ;
struct mt76x02_dev {scalar_t__ tx_hang_check; TYPE_3__ mt76; int /*<<< orphan*/  tx_hang_reset; scalar_t__ mcu_timeout; } ;

/* Variables and functions */
 scalar_t__ MT_TX_HANG_TH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ mt76x02_tx_hang (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_watchdog_reset (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x02_check_tx_hang(struct mt76x02_dev *dev)
{
	if (mt76x02_tx_hang(dev)) {
		if (++dev->tx_hang_check >= MT_TX_HANG_TH)
			goto restart;
	} else {
		dev->tx_hang_check = 0;
	}

	if (dev->mcu_timeout)
		goto restart;

	return;

restart:
	mt76x02_watchdog_reset(dev);

	mutex_lock(&dev->mt76.mmio.mcu.mutex);
	dev->mcu_timeout = 0;
	mutex_unlock(&dev->mt76.mmio.mcu.mutex);

	dev->tx_hang_reset++;
	dev->tx_hang_check = 0;
	memset(dev->mt76.tx_dma_idx, 0xff,
	       sizeof(dev->mt76.tx_dma_idx));
}