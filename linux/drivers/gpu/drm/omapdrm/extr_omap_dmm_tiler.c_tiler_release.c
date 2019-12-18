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
struct TYPE_3__ {scalar_t__ tcm; } ;
struct tiler_block {int /*<<< orphan*/  alloc_node; TYPE_1__ area; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct tiler_block*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 TYPE_2__* omap_dmm ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tcm_free (TYPE_1__*) ; 

int tiler_release(struct tiler_block *block)
{
	int ret = tcm_free(&block->area);
	unsigned long flags;

	if (block->area.tcm)
		dev_err(omap_dmm->dev, "failed to release block\n");

	spin_lock_irqsave(&list_lock, flags);
	list_del(&block->alloc_node);
	spin_unlock_irqrestore(&list_lock, flags);

	kfree(block);
	return ret;
}