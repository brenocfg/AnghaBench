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
typedef  int /*<<< orphan*/  u8 ;
struct zpci_dev {int /*<<< orphan*/  dma_table_lock; int /*<<< orphan*/  dma_table; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int ZPCI_PTE_INVALID ; 
 int ZPCI_PTE_VALID ; 
 int ZPCI_PTE_VALID_MASK ; 
 int /*<<< orphan*/  dma_update_cpu_trans (unsigned long*,int /*<<< orphan*/ *,int) ; 
 unsigned long* dma_walk_cpu_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __dma_update_trans(struct zpci_dev *zdev, unsigned long pa,
			      dma_addr_t dma_addr, size_t size, int flags)
{
	unsigned int nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	u8 *page_addr = (u8 *) (pa & PAGE_MASK);
	unsigned long irq_flags;
	unsigned long *entry;
	int i, rc = 0;

	if (!nr_pages)
		return -EINVAL;

	spin_lock_irqsave(&zdev->dma_table_lock, irq_flags);
	if (!zdev->dma_table) {
		rc = -EINVAL;
		goto out_unlock;
	}

	for (i = 0; i < nr_pages; i++) {
		entry = dma_walk_cpu_trans(zdev->dma_table, dma_addr);
		if (!entry) {
			rc = -ENOMEM;
			goto undo_cpu_trans;
		}
		dma_update_cpu_trans(entry, page_addr, flags);
		page_addr += PAGE_SIZE;
		dma_addr += PAGE_SIZE;
	}

undo_cpu_trans:
	if (rc && ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID)) {
		flags = ZPCI_PTE_INVALID;
		while (i-- > 0) {
			page_addr -= PAGE_SIZE;
			dma_addr -= PAGE_SIZE;
			entry = dma_walk_cpu_trans(zdev->dma_table, dma_addr);
			if (!entry)
				break;
			dma_update_cpu_trans(entry, page_addr, flags);
		}
	}
out_unlock:
	spin_unlock_irqrestore(&zdev->dma_table_lock, irq_flags);
	return rc;
}