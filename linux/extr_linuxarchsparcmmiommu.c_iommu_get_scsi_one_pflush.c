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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  flush_page_for_dma (unsigned long) ; 
 int /*<<< orphan*/  iommu_get_scsi_one (struct device*,char*,unsigned long) ; 

__attribute__((used)) static __u32 iommu_get_scsi_one_pflush(struct device *dev, char *vaddr, unsigned long len)
{
	unsigned long page = ((unsigned long) vaddr) & PAGE_MASK;

	while(page < ((unsigned long)(vaddr + len))) {
		flush_page_for_dma(page);
		page += PAGE_SIZE;
	}
	return iommu_get_scsi_one(dev, vaddr, len);
}