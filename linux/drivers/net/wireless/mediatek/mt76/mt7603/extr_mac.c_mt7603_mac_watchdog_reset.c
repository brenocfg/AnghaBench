#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  irqmask; } ;
struct TYPE_4__ {int beacon_int; int /*<<< orphan*/  hw; int /*<<< orphan*/ * napi; int /*<<< orphan*/  pre_tbtt_tasklet; int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  q_rx; int /*<<< orphan*/  q_tx; TYPE_1__ mmio; } ;
struct mt7603_dev {scalar_t__ cur_reset_cause; TYPE_2__ mt76; scalar_t__* reset_cause; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_FORCE_TX_EOF ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 scalar_t__ RESET_CAUSE_BEACON_STUCK ; 
 size_t RESET_CAUSE_RESET_FAILED ; 
 scalar_t__ RESET_CAUSE_RX_PSE_BUSY ; 
 scalar_t__ RESET_CAUSE_TX_HANG ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7603_beacon_set_timer (struct mt7603_dev*,int,int) ; 
 int /*<<< orphan*/  mt7603_dma_sched_reset (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_irq_disable (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7603_irq_enable (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7603_mac_dma_start (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_mac_stop (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_pse_client_reset (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_pse_reset (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_queue_rx_reset (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt76_queue_tx_cleanup (struct mt7603_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mt7603_mac_watchdog_reset(struct mt7603_dev *dev)
{
	int beacon_int = dev->mt76.beacon_int;
	u32 mask = dev->mt76.mmio.irqmask;
	int i;

	ieee80211_stop_queues(dev->mt76.hw);
	set_bit(MT76_RESET, &dev->mt76.state);

	/* lock/unlock all queues to ensure that no tx is pending */
	mt76_txq_schedule_all(&dev->mt76);

	tasklet_disable(&dev->mt76.tx_tasklet);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	napi_disable(&dev->mt76.napi[0]);
	napi_disable(&dev->mt76.napi[1]);
	napi_disable(&dev->mt76.tx_napi);

	mutex_lock(&dev->mt76.mutex);

	mt7603_beacon_set_timer(dev, -1, 0);

	if (dev->reset_cause[RESET_CAUSE_RESET_FAILED] ||
	    dev->cur_reset_cause == RESET_CAUSE_RX_PSE_BUSY ||
	    dev->cur_reset_cause == RESET_CAUSE_BEACON_STUCK ||
	    dev->cur_reset_cause == RESET_CAUSE_TX_HANG)
		mt7603_pse_reset(dev);

	if (dev->reset_cause[RESET_CAUSE_RESET_FAILED])
		goto skip_dma_reset;

	mt7603_mac_stop(dev);

	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_RX_DMA_EN | MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);
	usleep_range(1000, 2000);

	mt7603_irq_disable(dev, mask);

	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_FORCE_TX_EOF);

	mt7603_pse_client_reset(dev);

	for (i = 0; i < ARRAY_SIZE(dev->mt76.q_tx); i++)
		mt76_queue_tx_cleanup(dev, i, true);

	for (i = 0; i < ARRAY_SIZE(dev->mt76.q_rx); i++)
		mt76_queue_rx_reset(dev, i);

	mt7603_dma_sched_reset(dev);

	mt7603_mac_dma_start(dev);

	mt7603_irq_enable(dev, mask);

skip_dma_reset:
	clear_bit(MT76_RESET, &dev->mt76.state);
	mutex_unlock(&dev->mt76.mutex);

	tasklet_enable(&dev->mt76.tx_tasklet);
	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);

	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);
	mt7603_beacon_set_timer(dev, -1, beacon_int);

	napi_enable(&dev->mt76.napi[0]);
	napi_schedule(&dev->mt76.napi[0]);

	napi_enable(&dev->mt76.napi[1]);
	napi_schedule(&dev->mt76.napi[1]);

	ieee80211_wake_queues(dev->mt76.hw);
	mt76_txq_schedule_all(&dev->mt76);
}