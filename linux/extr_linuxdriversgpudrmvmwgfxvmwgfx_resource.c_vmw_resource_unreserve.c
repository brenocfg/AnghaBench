#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmw_resource {unsigned long backup_offset; int id; TYPE_4__* func; struct vmw_private* dev_priv; int /*<<< orphan*/  lru_head; scalar_t__ pin_count; struct vmw_buffer_object* backup; int /*<<< orphan*/  mob_head; } ;
struct vmw_private {int /*<<< orphan*/  resource_lock; int /*<<< orphan*/ * res_lru; } ;
struct TYPE_7__ {TYPE_2__* resv; } ;
struct vmw_buffer_object {int /*<<< orphan*/  res_list; TYPE_3__ base; } ;
struct TYPE_8__ {size_t res_type; int /*<<< orphan*/  may_evict; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {TYPE_1__ lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct vmw_buffer_object* vmw_bo_reference (struct vmw_buffer_object*) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void vmw_resource_unreserve(struct vmw_resource *res,
			    bool switch_backup,
			    struct vmw_buffer_object *new_backup,
			    unsigned long new_backup_offset)
{
	struct vmw_private *dev_priv = res->dev_priv;

	if (!list_empty(&res->lru_head))
		return;

	if (switch_backup && new_backup != res->backup) {
		if (res->backup) {
			lockdep_assert_held(&res->backup->base.resv->lock.base);
			list_del_init(&res->mob_head);
			vmw_bo_unreference(&res->backup);
		}

		if (new_backup) {
			res->backup = vmw_bo_reference(new_backup);
			lockdep_assert_held(&new_backup->base.resv->lock.base);
			list_add_tail(&res->mob_head, &new_backup->res_list);
		} else {
			res->backup = NULL;
		}
	}
	if (switch_backup)
		res->backup_offset = new_backup_offset;

	if (!res->func->may_evict || res->id == -1 || res->pin_count)
		return;

	write_lock(&dev_priv->resource_lock);
	list_add_tail(&res->lru_head,
		      &res->dev_priv->res_lru[res->func->res_type]);
	write_unlock(&dev_priv->resource_lock);
}