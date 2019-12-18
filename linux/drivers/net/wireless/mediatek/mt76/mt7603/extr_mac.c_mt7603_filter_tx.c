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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_DMA_FQCR0 ; 
 int MT_DMA_FQCR0_BUSY ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_DEST_PORT_ID ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_DEST_QUEUE_ID ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_TARGET_QID ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_TARGET_WCID ; 
 int /*<<< orphan*/  MT_TX_ABORT ; 
 int MT_TX_ABORT_EN ; 
 int /*<<< orphan*/  MT_TX_ABORT_WCID ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mt7603_wtbl_set_skip_tx (struct mt7603_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7603_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 

void mt7603_filter_tx(struct mt7603_dev *dev, int idx, bool abort)
{
	int i, port, queue;

	if (abort) {
		port = 3; /* PSE */
		queue = 8; /* free queue */
	} else {
		port = 0; /* HIF */
		queue = 1; /* MCU queue */
	}

	mt7603_wtbl_set_skip_tx(dev, idx, true);

	mt76_wr(dev, MT_TX_ABORT, MT_TX_ABORT_EN |
			FIELD_PREP(MT_TX_ABORT_WCID, idx));

	for (i = 0; i < 4; i++) {
		mt76_wr(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY |
			FIELD_PREP(MT_DMA_FQCR0_TARGET_WCID, idx) |
			FIELD_PREP(MT_DMA_FQCR0_TARGET_QID, i) |
			FIELD_PREP(MT_DMA_FQCR0_DEST_PORT_ID, port) |
			FIELD_PREP(MT_DMA_FQCR0_DEST_QUEUE_ID, queue));

		WARN_ON_ONCE(!mt76_poll(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY,
					0, 5000));
	}

	mt76_wr(dev, MT_TX_ABORT, 0);

	mt7603_wtbl_set_skip_tx(dev, idx, false);
}