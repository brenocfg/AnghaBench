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
typedef  unsigned long __u32 ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  iommu_release_one (struct device*,unsigned long,int) ; 

__attribute__((used)) static void iommu_release_scsi_one(struct device *dev, __u32 vaddr, unsigned long len)
{
	unsigned long off;
	int npages;

	off = vaddr & ~PAGE_MASK;
	npages = (off + len + PAGE_SIZE-1) >> PAGE_SHIFT;
	iommu_release_one(dev, vaddr & PAGE_MASK, npages);
}