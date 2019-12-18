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
struct uverbs_attr_bundle {int /*<<< orphan*/  context; } ;
struct uverbs_api_object {int /*<<< orphan*/  context; TYPE_1__* type_class; } ;
struct ib_uverbs_file {int /*<<< orphan*/  hw_destroy_rwsem; } ;
typedef  struct ib_uobject {int /*<<< orphan*/  context; TYPE_1__* type_class; } const ib_uobject ;
struct TYPE_2__ {struct uverbs_api_object* (* alloc_begin ) (struct uverbs_api_object const*,struct ib_uverbs_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 struct uverbs_api_object const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct uverbs_api_object const*) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 struct uverbs_api_object* stub1 (struct uverbs_api_object const*,struct ib_uverbs_file*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct ib_uobject *rdma_alloc_begin_uobject(const struct uverbs_api_object *obj,
					    struct ib_uverbs_file *ufile,
					    struct uverbs_attr_bundle *attrs)
{
	struct ib_uobject *ret;

	if (IS_ERR(obj))
		return ERR_PTR(-EINVAL);

	/*
	 * The hw_destroy_rwsem is held across the entire object creation and
	 * released during rdma_alloc_commit_uobject or
	 * rdma_alloc_abort_uobject
	 */
	if (!down_read_trylock(&ufile->hw_destroy_rwsem))
		return ERR_PTR(-EIO);

	ret = obj->type_class->alloc_begin(obj, ufile);
	if (IS_ERR(ret)) {
		up_read(&ufile->hw_destroy_rwsem);
		return ret;
	}
	if (attrs)
		attrs->context = ret->context;
	return ret;
}