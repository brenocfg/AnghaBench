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
struct TYPE_2__ {int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  napi_dev; int /*<<< orphan*/ * q_rx; int /*<<< orphan*/ * q_tx; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MT7615_RX_MCU_RING_SIZE ; 
 int /*<<< orphan*/  MT7615_RX_RING_SIZE ; 
 int /*<<< orphan*/  MT7615_TXQ_FWDL ; 
 int /*<<< orphan*/  MT7615_TXQ_MCU ; 
 int /*<<< orphan*/  MT7615_TX_FWDL_RING_SIZE ; 
 int /*<<< orphan*/  MT7615_TX_MCU_RING_SIZE ; 
 int /*<<< orphan*/  MT7615_TX_RING_SIZE ; 
 int MT_DELAY_INT_CFG ; 
 int MT_INT_RX_DONE_ALL ; 
 int MT_INT_TX_DONE_ALL ; 
 size_t MT_RXQ_MAIN ; 
 size_t MT_RXQ_MCU ; 
 int /*<<< orphan*/  MT_RX_BUF_SIZE ; 
 int /*<<< orphan*/  MT_RX_RING_BASE ; 
 size_t MT_TXQ_FWDL ; 
 size_t MT_TXQ_MCU ; 
 int MT_WPDMA_ABT_CFG ; 
 int MT_WPDMA_ABT_CFG1 ; 
 int MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG1 ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_DMA_BURST_SIZE ; 
 int MT_WPDMA_GLO_CFG_FIFO_LITTLE_ENDIAN ; 
 int MT_WPDMA_GLO_CFG_FIRST_TOKEN_ONLY ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_MULTI_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_OMIT_TX_INFO ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT0 ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT21 ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int MT_WPDMA_RST_IDX ; 
 int MT_WPDMA_RX_PRE_CFG ; 
 int MT_WPDMA_TX_PRE_CFG ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int mt7615_init_mcu_queue (struct mt7615_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt7615_init_tx_queues (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7615_irq_enable (struct mt7615_dev*,int) ; 
 int /*<<< orphan*/  mt7615_poll_tx ; 
 int /*<<< orphan*/  mt76_clear (struct mt7615_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_dma_attach (TYPE_1__*) ; 
 int mt76_init_queues (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7615_dev*,int,int,int /*<<< orphan*/ ,int) ; 
 int mt76_queue_alloc (struct mt7615_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7615_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7615_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int,int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt7615_dma_init(struct mt7615_dev *dev)
{
	int ret;

	mt76_dma_attach(&dev->mt76);

	mt76_wr(dev, MT_WPDMA_GLO_CFG,
		MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE |
		MT_WPDMA_GLO_CFG_FIFO_LITTLE_ENDIAN |
		MT_WPDMA_GLO_CFG_FIRST_TOKEN_ONLY |
		MT_WPDMA_GLO_CFG_OMIT_TX_INFO);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT0, 0x1);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT21, 0x1);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 0x3);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_MULTI_DMA_EN, 0x3);

	mt76_wr(dev, MT_WPDMA_GLO_CFG1, 0x1);
	mt76_wr(dev, MT_WPDMA_TX_PRE_CFG, 0xf0000);
	mt76_wr(dev, MT_WPDMA_RX_PRE_CFG, 0xf7f0000);
	mt76_wr(dev, MT_WPDMA_ABT_CFG, 0x4000026);
	mt76_wr(dev, MT_WPDMA_ABT_CFG1, 0x18811881);
	mt76_set(dev, 0x7158, BIT(16));
	mt76_clear(dev, 0x7000, BIT(23));
	mt76_wr(dev, MT_WPDMA_RST_IDX, ~0);

	ret = mt7615_init_tx_queues(dev, MT7615_TX_RING_SIZE);
	if (ret)
		return ret;

	ret = mt7615_init_mcu_queue(dev, &dev->mt76.q_tx[MT_TXQ_MCU],
				    MT7615_TXQ_MCU,
				    MT7615_TX_MCU_RING_SIZE);
	if (ret)
		return ret;

	ret = mt7615_init_mcu_queue(dev, &dev->mt76.q_tx[MT_TXQ_FWDL],
				    MT7615_TXQ_FWDL,
				    MT7615_TX_FWDL_RING_SIZE);
	if (ret)
		return ret;

	/* init rx queues */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MCU], 1,
			       MT7615_RX_MCU_RING_SIZE, MT_RX_BUF_SIZE,
			       MT_RX_RING_BASE);
	if (ret)
		return ret;

	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MAIN], 0,
			       MT7615_RX_RING_SIZE, MT_RX_BUF_SIZE,
			       MT_RX_RING_BASE);
	if (ret)
		return ret;

	mt76_wr(dev, MT_DELAY_INT_CFG, 0);

	ret = mt76_init_queues(dev);
	if (ret < 0)
		return ret;

	netif_tx_napi_add(&dev->mt76.napi_dev, &dev->mt76.tx_napi,
			  mt7615_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	mt76_poll(dev, MT_WPDMA_GLO_CFG,
		  MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		  MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 1000);

	/* start dma engine */
	mt76_set(dev, MT_WPDMA_GLO_CFG,
		 MT_WPDMA_GLO_CFG_TX_DMA_EN |
		 MT_WPDMA_GLO_CFG_RX_DMA_EN);

	/* enable interrupts for TX/RX rings */
	mt7615_irq_enable(dev, MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL);

	return 0;
}