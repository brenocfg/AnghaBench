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
struct TYPE_4__ {int /*<<< orphan*/ * napi; int /*<<< orphan*/  tx_napi; TYPE_1__ mmio; int /*<<< orphan*/  state; } ;
struct mt7615_dev {TYPE_2__ mt76; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int MT_INT_RX_DONE (int) ; 
 int /*<<< orphan*/  MT_INT_SOURCE_CSR ; 
 int MT_INT_TX_DONE_ALL ; 
 int /*<<< orphan*/  mt7615_irq_disable (struct mt7615_dev*,int) ; 
 int mt76_rr (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mt7615_irq_handler(int irq, void *dev_instance)
{
	struct mt7615_dev *dev = dev_instance;
	u32 intr;

	intr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	mt76_wr(dev, MT_INT_SOURCE_CSR, intr);

	if (!test_bit(MT76_STATE_INITIALIZED, &dev->mt76.state))
		return IRQ_NONE;

	intr &= dev->mt76.mmio.irqmask;

	if (intr & MT_INT_TX_DONE_ALL) {
		mt7615_irq_disable(dev, MT_INT_TX_DONE_ALL);
		napi_schedule(&dev->mt76.tx_napi);
	}

	if (intr & MT_INT_RX_DONE(0)) {
		mt7615_irq_disable(dev, MT_INT_RX_DONE(0));
		napi_schedule(&dev->mt76.napi[0]);
	}

	if (intr & MT_INT_RX_DONE(1)) {
		mt7615_irq_disable(dev, MT_INT_RX_DONE(1));
		napi_schedule(&dev->mt76.napi[1]);
	}

	return IRQ_HANDLED;
}