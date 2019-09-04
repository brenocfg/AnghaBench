#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {unsigned int first_dma_page; unsigned int current_dma_page; unsigned long dma_type; unsigned int event_wrap; unsigned int nr_dma_pages; TYPE_2__* dma_pages; int /*<<< orphan*/  last_dma_age; TYPE_1__* cmd_dma; } ;
typedef  TYPE_3__ drm_savage_private_t ;
struct TYPE_7__ {unsigned int used; unsigned int flushed; int /*<<< orphan*/  age; } ;
struct TYPE_6__ {unsigned int offset; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCI_CMD_WAIT ; 
 int /*<<< orphan*/  BCI_DMA (unsigned int) ; 
 int /*<<< orphan*/  BCI_LOCALS ; 
 int /*<<< orphan*/  BCI_SET_REGISTERS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BCI_WRITE (unsigned long) ; 
 int /*<<< orphan*/  BEGIN_BCI (int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  SAVAGE_DMABUFADDR ; 
 unsigned int SAVAGE_DMA_PAGE_SIZE ; 
 int /*<<< orphan*/  SET_AGE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  savage_bci_emit_event (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void savage_dma_flush(drm_savage_private_t * dev_priv)
{
	unsigned int first = dev_priv->first_dma_page;
	unsigned int cur = dev_priv->current_dma_page;
	uint16_t event;
	unsigned int wrap, pad, align, len, i;
	unsigned long phys_addr;
	BCI_LOCALS;

	if (first == cur &&
	    dev_priv->dma_pages[cur].used == dev_priv->dma_pages[cur].flushed)
		return;

	/* pad length to multiples of 2 entries
	 * align start of next DMA block to multiles of 8 entries */
	pad = -dev_priv->dma_pages[cur].used & 1;
	align = -(dev_priv->dma_pages[cur].used + pad) & 7;

	DRM_DEBUG("first=%u, cur=%u, first->flushed=%u, cur->used=%u, "
		  "pad=%u, align=%u\n",
		  first, cur, dev_priv->dma_pages[first].flushed,
		  dev_priv->dma_pages[cur].used, pad, align);

	/* pad with noops */
	if (pad) {
		uint32_t *dma_ptr = (uint32_t *) dev_priv->cmd_dma->handle +
		    cur * SAVAGE_DMA_PAGE_SIZE + dev_priv->dma_pages[cur].used;
		dev_priv->dma_pages[cur].used += pad;
		while (pad != 0) {
			*dma_ptr++ = BCI_CMD_WAIT;
			pad--;
		}
	}

	mb();

	/* do flush ... */
	phys_addr = dev_priv->cmd_dma->offset +
	    (first * SAVAGE_DMA_PAGE_SIZE +
	     dev_priv->dma_pages[first].flushed) * 4;
	len = (cur - first) * SAVAGE_DMA_PAGE_SIZE +
	    dev_priv->dma_pages[cur].used - dev_priv->dma_pages[first].flushed;

	DRM_DEBUG("phys_addr=%lx, len=%u\n",
		  phys_addr | dev_priv->dma_type, len);

	BEGIN_BCI(3);
	BCI_SET_REGISTERS(SAVAGE_DMABUFADDR, 1);
	BCI_WRITE(phys_addr | dev_priv->dma_type);
	BCI_DMA(len);

	/* fix alignment of the start of the next block */
	dev_priv->dma_pages[cur].used += align;

	/* age DMA pages */
	event = savage_bci_emit_event(dev_priv, 0);
	wrap = dev_priv->event_wrap;
	for (i = first; i < cur; ++i) {
		SET_AGE(&dev_priv->dma_pages[i].age, event, wrap);
		dev_priv->dma_pages[i].used = 0;
		dev_priv->dma_pages[i].flushed = 0;
	}
	/* age the current page only when it's full */
	if (dev_priv->dma_pages[cur].used == SAVAGE_DMA_PAGE_SIZE) {
		SET_AGE(&dev_priv->dma_pages[cur].age, event, wrap);
		dev_priv->dma_pages[cur].used = 0;
		dev_priv->dma_pages[cur].flushed = 0;
		/* advance to next page */
		cur++;
		if (cur == dev_priv->nr_dma_pages)
			cur = 0;
		dev_priv->first_dma_page = dev_priv->current_dma_page = cur;
	} else {
		dev_priv->first_dma_page = cur;
		dev_priv->dma_pages[cur].flushed = dev_priv->dma_pages[i].used;
	}
	SET_AGE(&dev_priv->last_dma_age, event, wrap);

	DRM_DEBUG("first=cur=%u, cur->used=%u, cur->flushed=%u\n", cur,
		  dev_priv->dma_pages[cur].used,
		  dev_priv->dma_pages[cur].flushed);
}