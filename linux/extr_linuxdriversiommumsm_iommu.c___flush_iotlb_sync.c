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

/* Variables and functions */

__attribute__((used)) static void __flush_iotlb_sync(void *cookie)
{
	/*
	 * Nothing is needed here, the barrier to guarantee
	 * completion of the tlb sync operation is implicitly
	 * taken care when the iommu client does a writel before
	 * kick starting the other master.
	 */
}