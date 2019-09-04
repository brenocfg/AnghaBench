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
struct port_buffer {unsigned int sgpages; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma; struct port_buffer* buf; int /*<<< orphan*/  size; int /*<<< orphan*/  list; int /*<<< orphan*/ * sg; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_bufs_lock ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct port_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_rproc_enabled ; 
 int /*<<< orphan*/  kfree (struct port_buffer*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_free_dma_bufs ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* sg_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_buf(struct port_buffer *buf, bool can_sleep)
{
	unsigned int i;

	for (i = 0; i < buf->sgpages; i++) {
		struct page *page = sg_page(&buf->sg[i]);
		if (!page)
			break;
		put_page(page);
	}

	if (!buf->dev) {
		kfree(buf->buf);
	} else if (is_rproc_enabled) {
		unsigned long flags;

		/* dma_free_coherent requires interrupts to be enabled. */
		if (!can_sleep) {
			/* queue up dma-buffers to be freed later */
			spin_lock_irqsave(&dma_bufs_lock, flags);
			list_add_tail(&buf->list, &pending_free_dma_bufs);
			spin_unlock_irqrestore(&dma_bufs_lock, flags);
			return;
		}
		dma_free_coherent(buf->dev, buf->size, buf->buf, buf->dma);

		/* Release device refcnt and allow it to be freed */
		put_device(buf->dev);
	}

	kfree(buf);
}