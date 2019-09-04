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
struct ddb_input {TYPE_2__* dma; TYPE_1__* port; } ;
struct ddb {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ running; } ;
struct TYPE_3__ {int /*<<< orphan*/  lnr; struct ddb* dev; } ;

/* Variables and functions */
 int DDB_LINK_TAG (int /*<<< orphan*/ ) ; 
 int DMA_BUFFER_CONTROL (TYPE_2__*) ; 
 int TS_CONTROL (struct ddb_input*) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddb_input_stop(struct ddb_input *input)
{
	struct ddb *dev = input->port->dev;
	u32 tag = DDB_LINK_TAG(input->port->lnr);

	spin_lock_irq(&input->dma->lock);

	ddbwritel(dev, 0, tag | TS_CONTROL(input));

	ddbwritel(dev, 0, DMA_BUFFER_CONTROL(input->dma));
	input->dma->running = 0;
	spin_unlock_irq(&input->dma->lock);
}