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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __sme_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static inline u64 iommu_virt_to_phys(void *vaddr)
{
	return (u64)__sme_set(virt_to_phys(vaddr));
}