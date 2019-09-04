#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct resource {int /*<<< orphan*/  end; struct resource* sibling; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {struct resource* child; } ;

/* Variables and functions */
 TYPE_1__ iomem_resource ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 drm_get_max_iomem(void)
{
	struct resource *tmp;
	resource_size_t max_iomem = 0;

	for (tmp = iomem_resource.child; tmp; tmp = tmp->sibling) {
		max_iomem = max(max_iomem,  tmp->end);
	}

	return max_iomem;
}