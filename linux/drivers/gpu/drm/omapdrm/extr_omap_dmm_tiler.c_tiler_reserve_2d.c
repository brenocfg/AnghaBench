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
typedef  scalar_t__ u16 ;
struct tiler_block {int fmt; int /*<<< orphan*/  alloc_node; int /*<<< orphan*/  area; } ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;
struct TYPE_4__ {scalar_t__ slot_w; scalar_t__ slot_h; scalar_t__ cpp; } ;
struct TYPE_3__ {int /*<<< orphan*/  alloc_head; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tiler_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * containers ; 
 TYPE_2__* geom ; 
 int /*<<< orphan*/  kfree (struct tiler_block*) ; 
 struct tiler_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 TYPE_1__* omap_dmm ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tcm_reserve_2d (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validfmt (int) ; 

struct tiler_block *tiler_reserve_2d(enum tiler_fmt fmt, u16 w,
		u16 h, u16 align)
{
	struct tiler_block *block;
	u32 min_align = 128;
	int ret;
	unsigned long flags;
	u32 slot_bytes;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block)
		return ERR_PTR(-ENOMEM);

	BUG_ON(!validfmt(fmt));

	/* convert width/height to slots */
	w = DIV_ROUND_UP(w, geom[fmt].slot_w);
	h = DIV_ROUND_UP(h, geom[fmt].slot_h);

	/* convert alignment to slots */
	slot_bytes = geom[fmt].slot_w * geom[fmt].cpp;
	min_align = max(min_align, slot_bytes);
	align = (align > min_align) ? ALIGN(align, min_align) : min_align;
	align /= slot_bytes;

	block->fmt = fmt;

	ret = tcm_reserve_2d(containers[fmt], w, h, align, -1, slot_bytes,
			&block->area);
	if (ret) {
		kfree(block);
		return ERR_PTR(-ENOMEM);
	}

	/* add to allocation list */
	spin_lock_irqsave(&list_lock, flags);
	list_add(&block->alloc_node, &omap_dmm->alloc_head);
	spin_unlock_irqrestore(&list_lock, flags);

	return block;
}