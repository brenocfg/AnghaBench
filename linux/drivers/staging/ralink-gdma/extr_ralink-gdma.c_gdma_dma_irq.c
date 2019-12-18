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
typedef  int u32 ;
struct gdma_dma_dev {int /*<<< orphan*/  task; scalar_t__ chan_issued; int /*<<< orphan*/  cnt; int /*<<< orphan*/ * chan; TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int done_int_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdma_dma_chan_irq (struct gdma_dma_dev*,int /*<<< orphan*/ *) ; 
 int gdma_dma_read (struct gdma_dma_dev*,int) ; 
 int /*<<< orphan*/  gdma_dma_write (struct gdma_dma_dev*,int,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t gdma_dma_irq(int irq, void *devid)
{
	struct gdma_dma_dev *dma_dev = devid;
	u32 done, done_reg;
	unsigned int i;

	done_reg = dma_dev->data->done_int_reg;
	done = gdma_dma_read(dma_dev, done_reg);
	if (unlikely(!done))
		return IRQ_NONE;

	/* clean done bits */
	gdma_dma_write(dma_dev, done_reg, done);

	i = 0;
	while (done) {
		if (done & 0x1) {
			gdma_dma_chan_irq(dma_dev, &dma_dev->chan[i]);
			atomic_dec(&dma_dev->cnt);
		}
		done >>= 1;
		i++;
	}

	/* start only have work to do */
	if (dma_dev->chan_issued)
		tasklet_schedule(&dma_dev->task);

	return IRQ_HANDLED;
}