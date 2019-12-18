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
struct dmar_domain {int /*<<< orphan*/  agaw; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int VTD_PAGE_SHIFT ; 
 int agaw_to_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int domain_pfn_supported(struct dmar_domain *domain,
				       unsigned long pfn)
{
	int addr_width = agaw_to_width(domain->agaw) - VTD_PAGE_SHIFT;

	return !(addr_width < BITS_PER_LONG && pfn >> addr_width);
}