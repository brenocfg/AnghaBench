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
struct vmw_resource {size_t backup_size; size_t id; } ;
struct vmw_cotable {int seen_entries; size_t type; scalar_t__ scrubbed; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 TYPE_1__* co_info ; 
 scalar_t__ likely (int) ; 
 struct vmw_cotable* vmw_cotable (struct vmw_resource*) ; 
 int vmw_cotable_resize (struct vmw_resource*,size_t) ; 
 int vmw_cotable_unscrub (struct vmw_resource*) ; 
 scalar_t__ vmw_resource_mob_attached (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_cotable_create(struct vmw_resource *res)
{
	struct vmw_cotable *vcotbl = vmw_cotable(res);
	size_t new_size = res->backup_size;
	size_t needed_size;
	int ret;

	/* Check whether we need to resize the cotable */
	needed_size = (vcotbl->seen_entries + 1) * co_info[vcotbl->type].size;
	while (needed_size > new_size)
		new_size *= 2;

	if (likely(new_size <= res->backup_size)) {
		if (vcotbl->scrubbed && vmw_resource_mob_attached(res)) {
			ret = vmw_cotable_unscrub(res);
			if (ret)
				return ret;
		}
		res->id = vcotbl->type;
		return 0;
	}

	return vmw_cotable_resize(res, new_size);
}