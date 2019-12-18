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
struct omap_mbox {TYPE_1__* rxq; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RX ; 
 int /*<<< orphan*/  _omap_mbox_disable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct omap_mbox*) ; 
 int /*<<< orphan*/  mbox_queue_free (TYPE_1__*) ; 

__attribute__((used)) static void omap_mbox_fini(struct omap_mbox *mbox)
{
	_omap_mbox_disable_irq(mbox, IRQ_RX);
	free_irq(mbox->irq, mbox);
	flush_work(&mbox->rxq->work);
	mbox_queue_free(mbox->rxq);
}