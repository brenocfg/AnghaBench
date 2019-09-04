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
struct vmw_resource {int id; int res_dirty; TYPE_1__* backup; int /*<<< orphan*/  mob_head; struct vmw_res_func* func; } ;
struct vmw_res_func {int (* create ) (struct vmw_resource*) ;int (* bind ) (struct vmw_resource*,struct ttm_validate_buffer*) ;int /*<<< orphan*/  (* destroy ) (struct vmw_resource*) ;scalar_t__ needs_backup; } ;
struct ttm_validate_buffer {int /*<<< orphan*/ * bo; } ;
struct TYPE_2__ {int /*<<< orphan*/  res_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct vmw_resource*) ; 
 int stub2 (struct vmw_resource*,struct ttm_validate_buffer*) ; 
 int /*<<< orphan*/  stub3 (struct vmw_resource*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vmw_resource_do_validate(struct vmw_resource *res,
				    struct ttm_validate_buffer *val_buf)
{
	int ret = 0;
	const struct vmw_res_func *func = res->func;

	if (unlikely(res->id == -1)) {
		ret = func->create(res);
		if (unlikely(ret != 0))
			return ret;
	}

	if (func->bind &&
	    ((func->needs_backup && list_empty(&res->mob_head) &&
	      val_buf->bo != NULL) ||
	     (!func->needs_backup && val_buf->bo != NULL))) {
		ret = func->bind(res, val_buf);
		if (unlikely(ret != 0))
			goto out_bind_failed;
		if (func->needs_backup)
			list_add_tail(&res->mob_head, &res->backup->res_list);
	}

	/*
	 * Only do this on write operations, and move to
	 * vmw_resource_unreserve if it can be called after
	 * backup buffers have been unreserved. Otherwise
	 * sort out locking.
	 */
	res->res_dirty = true;

	return 0;

out_bind_failed:
	func->destroy(res);

	return ret;
}