#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct b43legacy_pio {TYPE_4__* queue3; TYPE_3__* queue2; TYPE_2__* queue1; TYPE_1__* queue0; } ;
struct b43legacy_wldev {struct b43legacy_pio pio; } ;
struct TYPE_8__ {int /*<<< orphan*/  txtask; int /*<<< orphan*/  txqueue; scalar_t__ tx_frozen; } ;
struct TYPE_7__ {int /*<<< orphan*/  txtask; int /*<<< orphan*/  txqueue; scalar_t__ tx_frozen; } ;
struct TYPE_6__ {int /*<<< orphan*/  txtask; int /*<<< orphan*/  txqueue; scalar_t__ tx_frozen; } ;
struct TYPE_5__ {int /*<<< orphan*/  txtask; int /*<<< orphan*/  txqueue; scalar_t__ tx_frozen; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_using_pio (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void b43legacy_pio_thaw_txqueues(struct b43legacy_wldev *dev)
{
	struct b43legacy_pio *pio;

	B43legacy_WARN_ON(!b43legacy_using_pio(dev));
	pio = &dev->pio;
	pio->queue0->tx_frozen = 0;
	pio->queue1->tx_frozen = 0;
	pio->queue2->tx_frozen = 0;
	pio->queue3->tx_frozen = 0;
	if (!list_empty(&pio->queue0->txqueue))
		tasklet_schedule(&pio->queue0->txtask);
	if (!list_empty(&pio->queue1->txqueue))
		tasklet_schedule(&pio->queue1->txtask);
	if (!list_empty(&pio->queue2->txqueue))
		tasklet_schedule(&pio->queue2->txtask);
	if (!list_empty(&pio->queue3->txqueue))
		tasklet_schedule(&pio->queue3->txtask);
}