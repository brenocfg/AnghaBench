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
struct ww_acquire_ctx {int dummy; } ;
struct vmw_resource {int res_dirty; int backup_dirty; struct vmw_res_func* func; } ;
struct vmw_res_func {int (* unbind ) (struct vmw_resource*,int,struct ttm_validate_buffer*) ;int (* destroy ) (struct vmw_resource*) ;int /*<<< orphan*/  needs_backup; int /*<<< orphan*/  may_evict; } ;
struct ttm_validate_buffer {scalar_t__ num_shared; int /*<<< orphan*/ * bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int stub1 (struct vmw_resource*,int,struct ttm_validate_buffer*) ; 
 int stub2 (struct vmw_resource*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_resource_backoff_reservation (struct ww_acquire_ctx*,struct ttm_validate_buffer*) ; 
 int vmw_resource_check_buffer (struct ww_acquire_ctx*,struct vmw_resource*,int,struct ttm_validate_buffer*) ; 
 scalar_t__ vmw_resource_mob_attached (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_mob_detach (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_resource_do_evict(struct ww_acquire_ctx *ticket,
				 struct vmw_resource *res, bool interruptible)
{
	struct ttm_validate_buffer val_buf;
	const struct vmw_res_func *func = res->func;
	int ret;

	BUG_ON(!func->may_evict);

	val_buf.bo = NULL;
	val_buf.num_shared = 0;
	ret = vmw_resource_check_buffer(ticket, res, interruptible, &val_buf);
	if (unlikely(ret != 0))
		return ret;

	if (unlikely(func->unbind != NULL &&
		     (!func->needs_backup || vmw_resource_mob_attached(res)))) {
		ret = func->unbind(res, res->res_dirty, &val_buf);
		if (unlikely(ret != 0))
			goto out_no_unbind;
		vmw_resource_mob_detach(res);
	}
	ret = func->destroy(res);
	res->backup_dirty = true;
	res->res_dirty = false;
out_no_unbind:
	vmw_resource_backoff_reservation(ticket, &val_buf);

	return ret;
}