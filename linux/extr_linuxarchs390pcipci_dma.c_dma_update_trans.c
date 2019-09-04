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
struct zpci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ZPCI_PTE_INVALID ; 
 int ZPCI_PTE_VALID ; 
 int ZPCI_PTE_VALID_MASK ; 
 int __dma_purge_tlb (struct zpci_dev*,int /*<<< orphan*/ ,size_t,int) ; 
 int __dma_update_trans (struct zpci_dev*,unsigned long,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int dma_update_trans(struct zpci_dev *zdev, unsigned long pa,
			    dma_addr_t dma_addr, size_t size, int flags)
{
	int rc;

	rc = __dma_update_trans(zdev, pa, dma_addr, size, flags);
	if (rc)
		return rc;

	rc = __dma_purge_tlb(zdev, dma_addr, size, flags);
	if (rc && ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID))
		__dma_update_trans(zdev, pa, dma_addr, size, ZPCI_PTE_INVALID);

	return rc;
}