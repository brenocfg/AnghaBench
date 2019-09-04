#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct titan_agp_aperture {scalar_t__ pg_start; int /*<<< orphan*/  arena; } ;
struct agp_memory {int /*<<< orphan*/  pages; int /*<<< orphan*/  page_count; } ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {struct titan_agp_aperture* sysdata; } ;
struct TYPE_5__ {TYPE_1__ aperture; } ;
typedef  TYPE_2__ alpha_agp_info ;

/* Variables and functions */
 int iommu_bind (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
titan_agp_bind_memory(alpha_agp_info *agp, off_t pg_start, struct agp_memory *mem)
{
	struct titan_agp_aperture *aper = agp->aperture.sysdata;
	return iommu_bind(aper->arena, aper->pg_start + pg_start, 
			  mem->page_count, mem->pages);
}