#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ddb_output {TYPE_4__* dma; TYPE_3__* port; } ;
struct ddb {int dummy; } ;
struct TYPE_10__ {int bufval; int running; int /*<<< orphan*/  lock; scalar_t__ stat; scalar_t__ coff; scalar_t__ cbuf; } ;
struct TYPE_9__ {TYPE_2__** input; struct ddb* dev; } ;
struct TYPE_8__ {TYPE_1__* port; } ;
struct TYPE_7__ {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ DDB_PORT_LOOP ; 
 int /*<<< orphan*/  DMA_BASE_READ ; 
 int /*<<< orphan*/  DMA_BUFFER_ACK (TYPE_4__*) ; 
 int /*<<< orphan*/  DMA_BUFFER_CONTROL (TYPE_4__*) ; 
 int /*<<< orphan*/  DMA_BUFFER_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  TS_CONTROL (struct ddb_output*) ; 
 int /*<<< orphan*/  TS_CONTROL2 (struct ddb_output*) ; 
 int /*<<< orphan*/  calc_con (struct ddb_output*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddb_output_start(struct ddb_output *output)
{
	struct ddb *dev = output->port->dev;
	u32 con = 0x11c, con2 = 0;

	spin_lock_irq(&output->dma->lock);
	output->dma->cbuf = 0;
	output->dma->coff = 0;
	output->dma->stat = 0;
	ddbwritel(dev, 0, DMA_BUFFER_CONTROL(output->dma));

	if (output->port->input[0]->port->class == DDB_PORT_LOOP)
		con = (1UL << 13) | 0x14;
	else
		calc_con(output, &con, &con2, 0);

	ddbwritel(dev, 0, TS_CONTROL(output));
	ddbwritel(dev, 2, TS_CONTROL(output));
	ddbwritel(dev, 0, TS_CONTROL(output));
	ddbwritel(dev, con, TS_CONTROL(output));
	ddbwritel(dev, con2, TS_CONTROL2(output));

	ddbwritel(dev, output->dma->bufval,
		  DMA_BUFFER_SIZE(output->dma));
	ddbwritel(dev, 0, DMA_BUFFER_ACK(output->dma));
	ddbwritel(dev, 1, DMA_BASE_READ);
	ddbwritel(dev, 7, DMA_BUFFER_CONTROL(output->dma));

	ddbwritel(dev, con | 1, TS_CONTROL(output));

	output->dma->running = 1;
	spin_unlock_irq(&output->dma->lock);
}