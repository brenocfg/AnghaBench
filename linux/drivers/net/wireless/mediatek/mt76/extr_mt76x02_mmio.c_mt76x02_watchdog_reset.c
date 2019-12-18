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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  irqmask; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; int /*<<< orphan*/ * napi; int /*<<< orphan*/  pre_tbtt_tasklet; int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; scalar_t__ beacon_mask; int /*<<< orphan*/ * q_rx; int /*<<< orphan*/ * q_tx; TYPE_2__* mcu_ops; TYPE_1__ mmio; } ;
struct mt76x02_dev {TYPE_3__ mt76; scalar_t__ ed_monitor; } ;
struct TYPE_5__ {int mcu_restart; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MT76_RESET ; 
 int MT_BEACON_TIME_CFG ; 
 int MT_BEACON_TIME_CFG_BEACON_TX ; 
 int MT_BEACON_TIME_CFG_TBTT_EN ; 
 int /*<<< orphan*/  MT_INT_SOURCE_CSR ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_TXOP_CTRL_CFG ; 
 int MT_TXOP_ED_CCA_EN ; 
 int MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 int /*<<< orphan*/  Q_SELECT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_restart_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_mcu_restart (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_queue_rx_reset (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76_queue_tx_cleanup (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (TYPE_3__*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_irq_disable (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_irq_enable (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_mac_start (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_mcu_function_select (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_reset_state (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mt76x02_watchdog_reset(struct mt76x02_dev *dev)
{
	u32 mask = dev->mt76.mmio.irqmask;
	bool restart = dev->mt76.mcu_ops->mcu_restart;
	int i;

	ieee80211_stop_queues(dev->mt76.hw);
	set_bit(MT76_RESET, &dev->mt76.state);

	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	tasklet_disable(&dev->mt76.tx_tasklet);
	napi_disable(&dev->mt76.tx_napi);

	for (i = 0; i < ARRAY_SIZE(dev->mt76.napi); i++)
		napi_disable(&dev->mt76.napi[i]);

	mutex_lock(&dev->mt76.mutex);

	if (restart)
		mt76x02_reset_state(dev);

	if (dev->mt76.beacon_mask)
		mt76_clear(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_BEACON_TX |
			   MT_BEACON_TIME_CFG_TBTT_EN);

	mt76x02_irq_disable(dev, mask);

	/* perform device reset */
	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
	mt76_wr(dev, MT_MAC_SYS_CTRL, 0);
	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_DMA_EN | MT_WPDMA_GLO_CFG_RX_DMA_EN);
	usleep_range(5000, 10000);
	mt76_wr(dev, MT_INT_SOURCE_CSR, 0xffffffff);

	/* let fw reset DMA */
	mt76_set(dev, 0x734, 0x3);

	if (restart)
		mt76_mcu_restart(dev);

	for (i = 0; i < ARRAY_SIZE(dev->mt76.q_tx); i++)
		mt76_queue_tx_cleanup(dev, i, true);

	for (i = 0; i < ARRAY_SIZE(dev->mt76.q_rx); i++)
		mt76_queue_rx_reset(dev, i);

	mt76x02_mac_start(dev);

	if (dev->ed_monitor)
		mt76_set(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);

	if (dev->mt76.beacon_mask && !restart)
		mt76_set(dev, MT_BEACON_TIME_CFG,
			 MT_BEACON_TIME_CFG_BEACON_TX |
			 MT_BEACON_TIME_CFG_TBTT_EN);

	mt76x02_irq_enable(dev, mask);

	mutex_unlock(&dev->mt76.mutex);

	clear_bit(MT76_RESET, &dev->mt76.state);

	tasklet_enable(&dev->mt76.tx_tasklet);
	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);

	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);

	for (i = 0; i < ARRAY_SIZE(dev->mt76.napi); i++) {
		napi_enable(&dev->mt76.napi[i]);
		napi_schedule(&dev->mt76.napi[i]);
	}

	if (restart) {
		mt76x02_mcu_function_select(dev, Q_SELECT, 1);
		ieee80211_restart_hw(dev->mt76.hw);
	} else {
		ieee80211_wake_queues(dev->mt76.hw);
		mt76_txq_schedule_all(&dev->mt76);
	}
}