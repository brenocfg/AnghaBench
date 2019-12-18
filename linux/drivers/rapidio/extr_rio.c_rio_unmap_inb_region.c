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
struct rio_mport {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_inb ) (struct rio_mport*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rio_mmap_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rio_mport*,int /*<<< orphan*/ ) ; 

void rio_unmap_inb_region(struct rio_mport *mport, dma_addr_t lstart)
{
	unsigned long flags;
	if (!mport->ops->unmap_inb)
		return;
	spin_lock_irqsave(&rio_mmap_lock, flags);
	mport->ops->unmap_inb(mport, lstart);
	spin_unlock_irqrestore(&rio_mmap_lock, flags);
}