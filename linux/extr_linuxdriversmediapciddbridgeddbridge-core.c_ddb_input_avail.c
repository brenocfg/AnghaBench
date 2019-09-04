#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ddb_input {TYPE_2__* dma; TYPE_1__* port; } ;
struct ddb {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int stat; int cbuf; } ;
struct TYPE_4__ {struct ddb* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_ACK (TYPE_2__*) ; 
 int /*<<< orphan*/  DMA_BUFFER_CONTROL (TYPE_2__*) ; 
 int ddbreadl (struct ddb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static u32 ddb_input_avail(struct ddb_input *input)
{
	struct ddb *dev = input->port->dev;
	u32 idx, off, stat = input->dma->stat;
	u32 ctrl = ddbreadl(dev, DMA_BUFFER_CONTROL(input->dma));

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	if (ctrl & 4) {
		dev_err(dev->dev, "IA %d %d %08x\n", idx, off, ctrl);
		ddbwritel(dev, stat, DMA_BUFFER_ACK(input->dma));
		return 0;
	}
	if (input->dma->cbuf != idx)
		return 188;
	return 0;
}