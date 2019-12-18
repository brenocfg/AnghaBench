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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_resource {int dummy; } ;
struct vmw_cmdbuf_res_manager {int dummy; } ;
struct list_head {int dummy; } ;
typedef  enum vmw_view_type { ____Placeholder_vmw_view_type } vmw_view_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 int vmw_cmdbuf_res_remove (struct vmw_cmdbuf_res_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct list_head*,struct vmw_resource**) ; 
 int /*<<< orphan*/  vmw_cmdbuf_res_view ; 
 int /*<<< orphan*/  vmw_view_id_ok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_view_key (int /*<<< orphan*/ ,int) ; 

int vmw_view_remove(struct vmw_cmdbuf_res_manager *man,
		    u32 user_key, enum vmw_view_type view_type,
		    struct list_head *list,
		    struct vmw_resource **res_p)
{
	if (!vmw_view_id_ok(user_key, view_type)) {
		VMW_DEBUG_USER("Illegal view remove view id.\n");
		return -EINVAL;
	}

	return vmw_cmdbuf_res_remove(man, vmw_cmdbuf_res_view,
				     vmw_view_key(user_key, view_type),
				     list, res_p);
}