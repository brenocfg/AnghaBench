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
struct videobuf_queue {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  sglist; int /*<<< orphan*/  magic; int /*<<< orphan*/  sglen; } ;
struct videobuf_dma_sg_memory {TYPE_1__ dma; int /*<<< orphan*/  magic; } ;
struct videobuf_buffer {struct videobuf_dma_sg_memory* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_DMABUF ; 
 int /*<<< orphan*/  MAGIC_SG_MEM ; 
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __videobuf_sync(struct videobuf_queue *q,
			   struct videobuf_buffer *buf)
{
	struct videobuf_dma_sg_memory *mem = buf->priv;
	BUG_ON(!mem || !mem->dma.sglen);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);
	MAGIC_CHECK(mem->dma.magic, MAGIC_DMABUF);

	dma_sync_sg_for_cpu(q->dev, mem->dma.sglist,
			    mem->dma.nr_pages, mem->dma.direction);

	return 0;
}