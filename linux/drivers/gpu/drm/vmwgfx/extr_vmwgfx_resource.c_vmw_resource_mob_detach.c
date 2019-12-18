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
struct vmw_resource {int /*<<< orphan*/  used_prio; int /*<<< orphan*/  mob_head; struct vmw_buffer_object* backup; } ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct vmw_buffer_object {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_prio_del (struct vmw_buffer_object*,int /*<<< orphan*/ ) ; 
 scalar_t__ vmw_resource_mob_attached (struct vmw_resource*) ; 

void vmw_resource_mob_detach(struct vmw_resource *res)
{
	struct vmw_buffer_object *backup = res->backup;

	dma_resv_assert_held(backup->base.base.resv);
	if (vmw_resource_mob_attached(res)) {
		list_del_init(&res->mob_head);
		vmw_bo_prio_del(backup, res->used_prio);
	}
}