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
struct vmw_resource {struct vmw_buffer_object* backup; TYPE_2__* func; int /*<<< orphan*/  backup_size; int /*<<< orphan*/  dev_priv; } ;
struct TYPE_3__ {unsigned long num_pages; } ;
struct vmw_buffer_object {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  backup_placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 struct vmw_buffer_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct vmw_buffer_object*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_bo_free ; 
 int vmw_bo_init (int /*<<< orphan*/ ,struct vmw_buffer_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_resource_buf_alloc(struct vmw_resource *res,
				  bool interruptible)
{
	unsigned long size =
		(res->backup_size + PAGE_SIZE - 1) & PAGE_MASK;
	struct vmw_buffer_object *backup;
	int ret;

	if (likely(res->backup)) {
		BUG_ON(res->backup->base.num_pages * PAGE_SIZE < size);
		return 0;
	}

	backup = kzalloc(sizeof(*backup), GFP_KERNEL);
	if (unlikely(!backup))
		return -ENOMEM;

	ret = vmw_bo_init(res->dev_priv, backup, res->backup_size,
			      res->func->backup_placement,
			      interruptible,
			      &vmw_bo_bo_free);
	if (unlikely(ret != 0))
		goto out_no_bo;

	res->backup = backup;

out_no_bo:
	return ret;
}