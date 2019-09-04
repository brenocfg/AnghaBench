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
struct uverbs_api_object {int dummy; } ;
struct ib_uverbs_file {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct ib_uobject {int /*<<< orphan*/  id; TYPE_1__* context; int /*<<< orphan*/  cg_obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct ib_uobject* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  RDMACG_RESOURCE_HCA_OBJECT ; 
 struct ib_uobject* alloc_uobj (struct ib_uverbs_file*,struct uverbs_api_object const*) ; 
 int ib_rdmacg_try_charge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int idr_add_uobj (struct ib_uobject*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_uobject_put (struct ib_uobject*) ; 

__attribute__((used)) static struct ib_uobject *
alloc_begin_idr_uobject(const struct uverbs_api_object *obj,
			struct ib_uverbs_file *ufile)
{
	int ret;
	struct ib_uobject *uobj;

	uobj = alloc_uobj(ufile, obj);
	if (IS_ERR(uobj))
		return uobj;

	ret = idr_add_uobj(uobj);
	if (ret)
		goto uobj_put;

	ret = ib_rdmacg_try_charge(&uobj->cg_obj, uobj->context->device,
				   RDMACG_RESOURCE_HCA_OBJECT);
	if (ret)
		goto idr_remove;

	return uobj;

idr_remove:
	spin_lock(&ufile->idr_lock);
	idr_remove(&ufile->idr, uobj->id);
	spin_unlock(&ufile->idr_lock);
uobj_put:
	uverbs_uobject_put(uobj);
	return ERR_PTR(ret);
}