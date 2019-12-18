#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vmw_resource {int /*<<< orphan*/  used_prio; int /*<<< orphan*/  mob_head; TYPE_3__* func; scalar_t__ res_dirty; struct vmw_buffer_object* backup; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct vmw_buffer_object {int /*<<< orphan*/  res_list; TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  dirty_prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_prio_add (struct vmw_buffer_object*,int /*<<< orphan*/ ) ; 

void vmw_resource_mob_attach(struct vmw_resource *res)
{
	struct vmw_buffer_object *backup = res->backup;

	dma_resv_assert_held(res->backup->base.base.resv);
	res->used_prio = (res->res_dirty) ? res->func->dirty_prio :
		res->func->prio;
	list_add_tail(&res->mob_head, &backup->res_list);
	vmw_bo_prio_add(backup, res->used_prio);
}