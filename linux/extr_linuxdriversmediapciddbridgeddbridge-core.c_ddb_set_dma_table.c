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
typedef  int u64 ;
typedef  size_t u32 ;
struct ddb_io {struct ddb_dma* dma; TYPE_1__* port; } ;
struct ddb_dma {size_t num; int* pbuf; int bufval; int div; int size; scalar_t__ bufregs; } ;
struct ddb {int dummy; } ;
struct TYPE_2__ {struct ddb* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,scalar_t__) ; 

__attribute__((used)) static void ddb_set_dma_table(struct ddb_io *io)
{
	struct ddb *dev = io->port->dev;
	struct ddb_dma *dma = io->dma;
	u32 i;
	u64 mem;

	if (!dma)
		return;
	for (i = 0; i < dma->num; i++) {
		mem = dma->pbuf[i];
		ddbwritel(dev, mem & 0xffffffff, dma->bufregs + i * 8);
		ddbwritel(dev, mem >> 32, dma->bufregs + i * 8 + 4);
	}
	dma->bufval = ((dma->div & 0x0f) << 16) |
		((dma->num & 0x1f) << 11) |
		((dma->size >> 7) & 0x7ff);
}