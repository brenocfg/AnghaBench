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
struct vmw_resource {int id; } ;
struct vmw_cotable {int seen_entries; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,int) ; 
 int EINVAL ; 
 int SVGA_COTABLE_MAX_IDS ; 
 struct vmw_cotable* vmw_cotable (struct vmw_resource*) ; 

int vmw_cotable_notify(struct vmw_resource *res, int id)
{
	struct vmw_cotable *vcotbl = vmw_cotable(res);

	if (id < 0 || id >= SVGA_COTABLE_MAX_IDS) {
		DRM_ERROR("Illegal COTable id. Type is %u. Id is %d\n",
			  (unsigned) vcotbl->type, id);
		return -EINVAL;
	}

	if (vcotbl->seen_entries < id) {
		/* Trigger a call to create() on next validate */
		res->id = -1;
		vcotbl->seen_entries = id;
	}

	return 0;
}