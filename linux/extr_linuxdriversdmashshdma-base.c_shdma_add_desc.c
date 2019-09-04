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
struct shdma_ops {int /*<<< orphan*/  (* desc_setup ) (struct shdma_chan*,struct shdma_desc*,size_t,size_t,size_t*) ;} ;
struct shdma_dev {struct shdma_ops* ops; } ;
struct TYPE_4__ {unsigned long flags; int /*<<< orphan*/  cookie; } ;
struct shdma_desc {int direction; scalar_t__ partial; TYPE_2__ async_tx; int /*<<< orphan*/  mark; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct shdma_chan {int /*<<< orphan*/  dev; TYPE_1__ dma_chan; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_PREPARED ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int DMA_MEM_TO_MEM ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,size_t,size_t*,size_t*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct shdma_desc* shdma_get_desc (struct shdma_chan*) ; 
 int /*<<< orphan*/  stub1 (struct shdma_chan*,struct shdma_desc*,size_t,size_t,size_t*) ; 
 struct shdma_dev* to_shdma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct shdma_desc *shdma_add_desc(struct shdma_chan *schan,
	unsigned long flags, dma_addr_t *dst, dma_addr_t *src, size_t *len,
	struct shdma_desc **first, enum dma_transfer_direction direction)
{
	struct shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	const struct shdma_ops *ops = sdev->ops;
	struct shdma_desc *new;
	size_t copy_size = *len;

	if (!copy_size)
		return NULL;

	/* Allocate the link descriptor from the free list */
	new = shdma_get_desc(schan);
	if (!new) {
		dev_err(schan->dev, "No free link descriptor available\n");
		return NULL;
	}

	ops->desc_setup(schan, new, *src, *dst, &copy_size);

	if (!*first) {
		/* First desc */
		new->async_tx.cookie = -EBUSY;
		*first = new;
	} else {
		/* Other desc - invisible to the user */
		new->async_tx.cookie = -EINVAL;
	}

	dev_dbg(schan->dev,
		"chaining (%zu/%zu)@%pad -> %pad with %p, cookie %d\n",
		copy_size, *len, src, dst, &new->async_tx,
		new->async_tx.cookie);

	new->mark = DESC_PREPARED;
	new->async_tx.flags = flags;
	new->direction = direction;
	new->partial = 0;

	*len -= copy_size;
	if (direction == DMA_MEM_TO_MEM || direction == DMA_MEM_TO_DEV)
		*src += copy_size;
	if (direction == DMA_MEM_TO_MEM || direction == DMA_DEV_TO_MEM)
		*dst += copy_size;

	return new;
}