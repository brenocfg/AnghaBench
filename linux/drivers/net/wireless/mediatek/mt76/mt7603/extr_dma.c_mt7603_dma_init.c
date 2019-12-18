#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  napi_dev; int /*<<< orphan*/ * q_rx; int /*<<< orphan*/ * q_tx; } ;
struct mt7603_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
#define  IEEE80211_AC_BE 131 
#define  IEEE80211_AC_BK 130 
#define  IEEE80211_AC_VI 129 
#define  IEEE80211_AC_VO 128 
 int /*<<< orphan*/  MT7603_RX_RING_SIZE ; 
 int /*<<< orphan*/  MT_DELAY_INT_CFG ; 
 int /*<<< orphan*/  MT_MCU_RING_SIZE ; 
 size_t MT_RXQ_MAIN ; 
 size_t MT_RXQ_MCU ; 
 int /*<<< orphan*/  MT_RX_BUF_SIZE ; 
 size_t MT_TXQ_BEACON ; 
 size_t MT_TXQ_CAB ; 
 size_t MT_TXQ_MCU ; 
 size_t MT_TXQ_PSD ; 
 int const MT_TX_HW_QUEUE_BCN ; 
 int const MT_TX_HW_QUEUE_BMC ; 
 int const MT_TX_HW_QUEUE_MCU ; 
 int const MT_TX_HW_QUEUE_MGMT ; 
 int /*<<< orphan*/  MT_TX_RING_SIZE ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_DMA_BURST_SIZE ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int /*<<< orphan*/  MT_WPDMA_RST_IDX ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int mt7603_init_rx_queue (struct mt7603_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt7603_init_tx_queue (struct mt7603_dev*,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7603_poll_tx ; 
 int /*<<< orphan*/  mt7603_pse_client_reset (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_dma_attach (TYPE_1__*) ; 
 int mt76_init_queues (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt7603_dma_init(struct mt7603_dev *dev)
{
	static const u8 wmm_queue_map[] = {
		[IEEE80211_AC_BK] = 0,
		[IEEE80211_AC_BE] = 1,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_VO] = 3,
	};
	int ret;
	int i;

	mt76_dma_attach(&dev->mt76);

	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_RX_DMA_EN |
		   MT_WPDMA_GLO_CFG_DMA_BURST_SIZE |
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);

	mt76_wr(dev, MT_WPDMA_RST_IDX, ~0);
	mt7603_pse_client_reset(dev);

	for (i = 0; i < ARRAY_SIZE(wmm_queue_map); i++) {
		ret = mt7603_init_tx_queue(dev, &dev->mt76.q_tx[i],
					   wmm_queue_map[i],
					   MT_TX_RING_SIZE);
		if (ret)
			return ret;
	}

	ret = mt7603_init_tx_queue(dev, &dev->mt76.q_tx[MT_TXQ_PSD],
				   MT_TX_HW_QUEUE_MGMT, MT_TX_RING_SIZE);
	if (ret)
		return ret;

	ret = mt7603_init_tx_queue(dev, &dev->mt76.q_tx[MT_TXQ_MCU],
				   MT_TX_HW_QUEUE_MCU, MT_MCU_RING_SIZE);
	if (ret)
		return ret;

	ret = mt7603_init_tx_queue(dev, &dev->mt76.q_tx[MT_TXQ_BEACON],
				   MT_TX_HW_QUEUE_BCN, MT_MCU_RING_SIZE);
	if (ret)
		return ret;

	ret = mt7603_init_tx_queue(dev, &dev->mt76.q_tx[MT_TXQ_CAB],
				   MT_TX_HW_QUEUE_BMC, MT_MCU_RING_SIZE);
	if (ret)
		return ret;

	ret = mt7603_init_rx_queue(dev, &dev->mt76.q_rx[MT_RXQ_MCU], 1,
				   MT_MCU_RING_SIZE, MT_RX_BUF_SIZE);
	if (ret)
		return ret;

	ret = mt7603_init_rx_queue(dev, &dev->mt76.q_rx[MT_RXQ_MAIN], 0,
				   MT7603_RX_RING_SIZE, MT_RX_BUF_SIZE);
	if (ret)
		return ret;

	mt76_wr(dev, MT_DELAY_INT_CFG, 0);
	ret = mt76_init_queues(dev);
	if (ret)
		return ret;

	netif_tx_napi_add(&dev->mt76.napi_dev, &dev->mt76.tx_napi,
			  mt7603_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	return 0;
}