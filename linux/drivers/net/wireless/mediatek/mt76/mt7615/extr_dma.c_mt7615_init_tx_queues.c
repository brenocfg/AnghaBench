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
struct mt76_sw_queue {struct mt76_queue* q; int /*<<< orphan*/  swq; } ;
struct mt76_queue {int dummy; } ;
struct TYPE_2__ {struct mt76_sw_queue* q_tx; int /*<<< orphan*/  dev; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MT_TXQ_MCU ; 
 int /*<<< orphan*/  MT_TX_RING_BASE ; 
 struct mt76_queue* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mt76_queue_alloc (struct mt7615_dev*,struct mt76_queue*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7615_init_tx_queues(struct mt7615_dev *dev, int n_desc)
{
	struct mt76_sw_queue *q;
	struct mt76_queue *hwq;
	int err, i;

	hwq = devm_kzalloc(dev->mt76.dev, sizeof(*hwq), GFP_KERNEL);
	if (!hwq)
		return -ENOMEM;

	err = mt76_queue_alloc(dev, hwq, 0, n_desc, 0, MT_TX_RING_BASE);
	if (err < 0)
		return err;

	for (i = 0; i < MT_TXQ_MCU; i++) {
		q = &dev->mt76.q_tx[i];
		INIT_LIST_HEAD(&q->swq);
		q->q = hwq;
	}

	return 0;
}