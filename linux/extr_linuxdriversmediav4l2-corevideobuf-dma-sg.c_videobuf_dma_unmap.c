#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct videobuf_dmabuf {scalar_t__ sglen; int /*<<< orphan*/ * sglist; int /*<<< orphan*/  direction; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  magic; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_DMABUF ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

int videobuf_dma_unmap(struct device *dev, struct videobuf_dmabuf *dma)
{
	MAGIC_CHECK(dma->magic, MAGIC_DMABUF);

	if (!dma->sglen)
		return 0;

	dma_unmap_sg(dev, dma->sglist, dma->nr_pages, dma->direction);

	vfree(dma->sglist);
	dma->sglist = NULL;
	dma->sglen = 0;

	return 0;
}