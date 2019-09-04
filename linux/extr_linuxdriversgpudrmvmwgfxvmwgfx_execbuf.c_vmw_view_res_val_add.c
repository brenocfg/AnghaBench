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
struct vmw_sw_context {int dummy; } ;
struct vmw_resource {int dummy; } ;

/* Variables and functions */
 int vmw_resource_val_add (struct vmw_sw_context*,struct vmw_resource*,int /*<<< orphan*/ *) ; 
 struct vmw_resource* vmw_view_srf (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_view_res_val_add(struct vmw_sw_context *sw_context,
				struct vmw_resource *view)
{
	int ret;

	/*
	 * First add the resource the view is pointing to, otherwise
	 * it may be swapped out when the view is validated.
	 */
	ret = vmw_resource_val_add(sw_context, vmw_view_srf(view), NULL);
	if (ret)
		return ret;

	return vmw_resource_val_add(sw_context, view, NULL);
}