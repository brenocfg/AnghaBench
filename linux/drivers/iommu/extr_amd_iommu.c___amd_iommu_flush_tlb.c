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
struct protection_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INV_IOMMU_ALL_PAGES_ADDRESS ; 
 int __flush_pasid (struct protection_domain*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __amd_iommu_flush_tlb(struct protection_domain *domain, int pasid)
{
	return __flush_pasid(domain, pasid, CMD_INV_IOMMU_ALL_PAGES_ADDRESS,
			     true);
}