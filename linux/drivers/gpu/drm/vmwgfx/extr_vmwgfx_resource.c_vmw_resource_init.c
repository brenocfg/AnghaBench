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
struct vmw_resource {void (* res_free ) (struct vmw_resource*) ;int id; int backup_dirty; int res_dirty; int used_prio; scalar_t__ backup_offset; int /*<<< orphan*/ * backup; int /*<<< orphan*/  binding_head; int /*<<< orphan*/  mob_head; int /*<<< orphan*/  lru_head; struct vmw_res_func const* func; struct vmw_private* dev_priv; int /*<<< orphan*/ * hw_destroy; int /*<<< orphan*/  kref; } ;
struct vmw_res_func {int dummy; } ;
struct vmw_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int vmw_resource_alloc_id (struct vmw_resource*) ; 

int vmw_resource_init(struct vmw_private *dev_priv, struct vmw_resource *res,
		      bool delay_id,
		      void (*res_free) (struct vmw_resource *res),
		      const struct vmw_res_func *func)
{
	kref_init(&res->kref);
	res->hw_destroy = NULL;
	res->res_free = res_free;
	res->dev_priv = dev_priv;
	res->func = func;
	INIT_LIST_HEAD(&res->lru_head);
	INIT_LIST_HEAD(&res->mob_head);
	INIT_LIST_HEAD(&res->binding_head);
	res->id = -1;
	res->backup = NULL;
	res->backup_offset = 0;
	res->backup_dirty = false;
	res->res_dirty = false;
	res->used_prio = 3;
	if (delay_id)
		return 0;
	else
		return vmw_resource_alloc_id(res);
}