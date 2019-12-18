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
struct urb {int /*<<< orphan*/  status; struct mt76_queue_entry* context; TYPE_1__* dev; } ;
struct mt76_queue_entry {int done; } ;
struct mt76_dev {int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mt76_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ mt76u_urb_error (struct urb*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76u_complete_tx(struct urb *urb)
{
	struct mt76_dev *dev = dev_get_drvdata(&urb->dev->dev);
	struct mt76_queue_entry *e = urb->context;

	if (mt76u_urb_error(urb))
		dev_err(dev->dev, "tx urb failed: %d\n", urb->status);
	e->done = true;

	tasklet_schedule(&dev->tx_tasklet);
}