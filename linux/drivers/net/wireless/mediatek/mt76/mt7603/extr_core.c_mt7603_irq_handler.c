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
typedef  int u32 ;
struct TYPE_3__ {int irqmask; } ;
struct TYPE_4__ {int /*<<< orphan*/ * napi; int /*<<< orphan*/  tx_napi; scalar_t__ csa_complete; int /*<<< orphan*/  pre_tbtt_tasklet; TYPE_1__ mmio; int /*<<< orphan*/  state; } ;
struct mt7603_dev {TYPE_2__ mt76; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int MT_HW_INT3_PRE_TBTT0 ; 
 int MT_HW_INT3_TBTT0 ; 
 int /*<<< orphan*/  MT_HW_INT_STATUS (int) ; 
 int MT_INT_MAC_IRQ3 ; 
 int MT_INT_RX_DONE (int) ; 
 int /*<<< orphan*/  MT_INT_SOURCE_CSR ; 
 int MT_INT_TX_DONE_ALL ; 
 int /*<<< orphan*/  mt7603_irq_disable (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt76_csa_finish (TYPE_2__*) ; 
 int mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t mt7603_irq_handler(int irq, void *dev_instance)
{
	struct mt7603_dev *dev = dev_instance;
	u32 intr;

	intr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	mt76_wr(dev, MT_INT_SOURCE_CSR, intr);

	if (!test_bit(MT76_STATE_INITIALIZED, &dev->mt76.state))
		return IRQ_NONE;

	intr &= dev->mt76.mmio.irqmask;

	if (intr & MT_INT_MAC_IRQ3) {
		u32 hwintr = mt76_rr(dev, MT_HW_INT_STATUS(3));

		mt76_wr(dev, MT_HW_INT_STATUS(3), hwintr);
		if (hwintr & MT_HW_INT3_PRE_TBTT0)
			tasklet_schedule(&dev->mt76.pre_tbtt_tasklet);

		if ((hwintr & MT_HW_INT3_TBTT0) && dev->mt76.csa_complete)
			mt76_csa_finish(&dev->mt76);
	}

	if (intr & MT_INT_TX_DONE_ALL) {
		mt7603_irq_disable(dev, MT_INT_TX_DONE_ALL);
		napi_schedule(&dev->mt76.tx_napi);
	}

	if (intr & MT_INT_RX_DONE(0)) {
		mt7603_irq_disable(dev, MT_INT_RX_DONE(0));
		napi_schedule(&dev->mt76.napi[0]);
	}

	if (intr & MT_INT_RX_DONE(1)) {
		mt7603_irq_disable(dev, MT_INT_RX_DONE(1));
		napi_schedule(&dev->mt76.napi[1]);
	}

	return IRQ_HANDLED;
}