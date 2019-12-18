#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct vmw_resource {int backup_dirty; TYPE_2__* backup; TYPE_1__* func; } ;
struct ttm_validate_buffer {int /*<<< orphan*/ * bo; int /*<<< orphan*/  head; scalar_t__ num_shared; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct list_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  backup_placement; scalar_t__ needs_backup; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  ttm_bo_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_put (int /*<<< orphan*/ *) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int ttm_eu_reserve_buffers (struct ww_acquire_ctx*,struct list_head*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (TYPE_2__**) ; 
 int vmw_resource_buf_alloc (struct vmw_resource*,int) ; 
 int /*<<< orphan*/  vmw_resource_mob_attached (struct vmw_resource*) ; 

__attribute__((used)) static int
vmw_resource_check_buffer(struct ww_acquire_ctx *ticket,
			  struct vmw_resource *res,
			  bool interruptible,
			  struct ttm_validate_buffer *val_buf)
{
	struct ttm_operation_ctx ctx = { true, false };
	struct list_head val_list;
	bool backup_dirty = false;
	int ret;

	if (unlikely(res->backup == NULL)) {
		ret = vmw_resource_buf_alloc(res, interruptible);
		if (unlikely(ret != 0))
			return ret;
	}

	INIT_LIST_HEAD(&val_list);
	ttm_bo_get(&res->backup->base);
	val_buf->bo = &res->backup->base;
	val_buf->num_shared = 0;
	list_add_tail(&val_buf->head, &val_list);
	ret = ttm_eu_reserve_buffers(ticket, &val_list, interruptible, NULL,
				     true);
	if (unlikely(ret != 0))
		goto out_no_reserve;

	if (res->func->needs_backup && !vmw_resource_mob_attached(res))
		return 0;

	backup_dirty = res->backup_dirty;
	ret = ttm_bo_validate(&res->backup->base,
			      res->func->backup_placement,
			      &ctx);

	if (unlikely(ret != 0))
		goto out_no_validate;

	return 0;

out_no_validate:
	ttm_eu_backoff_reservation(ticket, &val_list);
out_no_reserve:
	ttm_bo_put(val_buf->bo);
	val_buf->bo = NULL;
	if (backup_dirty)
		vmw_bo_unreference(&res->backup);

	return ret;
}