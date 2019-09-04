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
 int /*<<< orphan*/  enable_gart_translations () ; 
 int /*<<< orphan*/  gart_fixup_northbridges () ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void gart_resume(void)
{
	pr_info("PCI-DMA: Resuming GART IOMMU\n");

	gart_fixup_northbridges();

	enable_gart_translations();
}