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
struct comedi_subdevice {scalar_t__ async_dma_dir; int /*<<< orphan*/  spin_lock; struct comedi_async* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_buf_map {int dummy; } ;
struct comedi_async {struct comedi_buf_map* buf_map; scalar_t__ prealloc_bufsz; int /*<<< orphan*/ * prealloc_buf; } ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  comedi_buf_map_put (struct comedi_buf_map*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __comedi_buf_free(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_buf_map *bm;
	unsigned long flags;

	if (async->prealloc_buf) {
		if (s->async_dma_dir == DMA_NONE)
			vunmap(async->prealloc_buf);
		async->prealloc_buf = NULL;
		async->prealloc_bufsz = 0;
	}

	spin_lock_irqsave(&s->spin_lock, flags);
	bm = async->buf_map;
	async->buf_map = NULL;
	spin_unlock_irqrestore(&s->spin_lock, flags);
	comedi_buf_map_put(bm);
}