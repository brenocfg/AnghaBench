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
struct idma64_chip {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; struct idma64* idma64; } ;
struct TYPE_3__ {int /*<<< orphan*/  task; } ;
struct idma64_chan {TYPE_1__ vchan; } ;
struct TYPE_4__ {unsigned short chancnt; } ;
struct idma64 {struct idma64_chan* chan; TYPE_2__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct idma64*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idma64_remove(struct idma64_chip *chip)
{
	struct idma64 *idma64 = chip->idma64;
	unsigned short i;

	dma_async_device_unregister(&idma64->dma);

	/*
	 * Explicitly call devm_request_irq() to avoid the side effects with
	 * the scheduled tasklets.
	 */
	devm_free_irq(chip->dev, chip->irq, idma64);

	for (i = 0; i < idma64->dma.chancnt; i++) {
		struct idma64_chan *idma64c = &idma64->chan[i];

		tasklet_kill(&idma64c->vchan.task);
	}

	return 0;
}