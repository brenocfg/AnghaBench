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
typedef  scalar_t__ u32 ;
struct ispstat_buffer {int empty; int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ispstat {scalar_t__ buf_alloc_size; scalar_t__ state; TYPE_2__ subdev; TYPE_1__* isp; struct ispstat_buffer* buf; scalar_t__ buf_processing; int /*<<< orphan*/ * locked_buf; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; int /*<<< orphan*/  stat_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 scalar_t__ ISPSTAT_DISABLED ; 
 scalar_t__ ISP_STAT_USES_DMAENGINE (struct ispstat*) ; 
 unsigned int STAT_MAX_BUFS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int isp_stat_bufs_alloc_one (struct device*,struct ispstat_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  isp_stat_bufs_free (struct ispstat*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int isp_stat_bufs_alloc(struct ispstat *stat, u32 size)
{
	struct device *dev = ISP_STAT_USES_DMAENGINE(stat)
			   ? NULL : stat->isp->dev;
	unsigned long flags;
	unsigned int i;

	spin_lock_irqsave(&stat->isp->stat_lock, flags);

	BUG_ON(stat->locked_buf != NULL);

	/* Are the old buffers big enough? */
	if (stat->buf_alloc_size >= size) {
		spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
		return 0;
	}

	if (stat->state != ISPSTAT_DISABLED || stat->buf_processing) {
		dev_info(stat->isp->dev,
			 "%s: trying to allocate memory when busy\n",
			 stat->subdev.name);
		spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
		return -EBUSY;
	}

	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);

	isp_stat_bufs_free(stat);

	stat->buf_alloc_size = size;

	for (i = 0; i < STAT_MAX_BUFS; i++) {
		struct ispstat_buffer *buf = &stat->buf[i];
		int ret;

		ret = isp_stat_bufs_alloc_one(dev, buf, size);
		if (ret < 0) {
			dev_err(stat->isp->dev,
				"%s: Failed to allocate DMA buffer %u\n",
				stat->subdev.name, i);
			isp_stat_bufs_free(stat);
			return ret;
		}

		buf->empty = 1;

		dev_dbg(stat->isp->dev,
			"%s: buffer[%u] allocated. dma=%pad virt=%p",
			stat->subdev.name, i, &buf->dma_addr, buf->virt_addr);
	}

	return 0;
}