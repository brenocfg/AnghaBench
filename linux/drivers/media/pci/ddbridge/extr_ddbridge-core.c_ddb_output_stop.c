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
struct ddb_output {TYPE_2__* dma; TYPE_1__* port; } ;
struct ddb {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ running; } ;
struct TYPE_3__ {struct ddb* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_CONTROL (TYPE_2__*) ; 
 int /*<<< orphan*/  TS_CONTROL (struct ddb_output*) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddb_output_stop(struct ddb_output *output)
{
	struct ddb *dev = output->port->dev;

	spin_lock_irq(&output->dma->lock);

	ddbwritel(dev, 0, TS_CONTROL(output));

	ddbwritel(dev, 0, DMA_BUFFER_CONTROL(output->dma));
	output->dma->running = 0;
	spin_unlock_irq(&output->dma->lock);
}