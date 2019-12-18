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
struct ispstat_buffer {int empty; int /*<<< orphan*/ * virt_addr; scalar_t__ dma_addr; int /*<<< orphan*/  sgt; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ispstat {int /*<<< orphan*/ * active_buf; int /*<<< orphan*/  buf_alloc_size; TYPE_2__ subdev; TYPE_1__* isp; struct ispstat_buffer* buf; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ ISP_STAT_USES_DMAENGINE (struct ispstat*) ; 
 unsigned int STAT_MAX_BUFS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isp_stat_bufs_free(struct ispstat *stat)
{
	struct device *dev = ISP_STAT_USES_DMAENGINE(stat)
			   ? NULL : stat->isp->dev;
	unsigned int i;

	for (i = 0; i < STAT_MAX_BUFS; i++) {
		struct ispstat_buffer *buf = &stat->buf[i];

		if (!buf->virt_addr)
			continue;

		sg_free_table(&buf->sgt);

		dma_free_coherent(dev, stat->buf_alloc_size, buf->virt_addr,
				  buf->dma_addr);

		buf->dma_addr = 0;
		buf->virt_addr = NULL;
		buf->empty = 1;
	}

	dev_dbg(stat->isp->dev, "%s: all buffers were freed.\n",
		stat->subdev.name);

	stat->buf_alloc_size = 0;
	stat->active_buf = NULL;
}