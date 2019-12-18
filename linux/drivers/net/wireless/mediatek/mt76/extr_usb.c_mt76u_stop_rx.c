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
struct mt76_queue {int ndesc; TYPE_1__* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_tasklet; } ;
struct mt76_dev {TYPE_2__ usb; struct mt76_queue* q_rx; } ;
struct TYPE_3__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 size_t MT_RXQ_MAIN ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 

void mt76u_stop_rx(struct mt76_dev *dev)
{
	struct mt76_queue *q = &dev->q_rx[MT_RXQ_MAIN];
	int i;

	for (i = 0; i < q->ndesc; i++)
		usb_poison_urb(q->entry[i].urb);

	tasklet_kill(&dev->usb.rx_tasklet);
}