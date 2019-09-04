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
struct vmw_resource_relocation {unsigned long offset; int rel_type; int /*<<< orphan*/  head; struct vmw_resource const* res; } ;
struct vmw_resource {int dummy; } ;
struct list_head {int dummy; } ;
typedef  enum vmw_resource_relocation_type { ____Placeholder_vmw_resource_relocation_type } vmw_resource_relocation_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vmw_resource_relocation* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vmw_resource_relocation_add(struct list_head *list,
				       const struct vmw_resource *res,
				       unsigned long offset,
				       enum vmw_resource_relocation_type
				       rel_type)
{
	struct vmw_resource_relocation *rel;

	rel = kmalloc(sizeof(*rel), GFP_KERNEL);
	if (unlikely(!rel)) {
		DRM_ERROR("Failed to allocate a resource relocation.\n");
		return -ENOMEM;
	}

	rel->res = res;
	rel->offset = offset;
	rel->rel_type = rel_type;
	list_add_tail(&rel->head, list);

	return 0;
}