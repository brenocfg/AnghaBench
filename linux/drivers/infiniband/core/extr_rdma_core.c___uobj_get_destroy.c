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
typedef  int /*<<< orphan*/  u32 ;
struct uverbs_attr_bundle {int /*<<< orphan*/  ufile; } ;
struct uverbs_api_object {int dummy; } ;
struct ib_uobject {int dummy; } ;

/* Variables and functions */
 struct ib_uobject* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_DESTROY ; 
 struct ib_uobject* rdma_lookup_get_uobject (struct uverbs_api_object const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  rdma_lookup_put_uobject (struct ib_uobject*,int /*<<< orphan*/ ) ; 
 int uobj_destroy (struct ib_uobject*,struct uverbs_attr_bundle*) ; 

struct ib_uobject *__uobj_get_destroy(const struct uverbs_api_object *obj,
				      u32 id, struct uverbs_attr_bundle *attrs)
{
	struct ib_uobject *uobj;
	int ret;

	uobj = rdma_lookup_get_uobject(obj, attrs->ufile, id,
				       UVERBS_LOOKUP_DESTROY, attrs);
	if (IS_ERR(uobj))
		return uobj;

	ret = uobj_destroy(uobj, attrs);
	if (ret) {
		rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_DESTROY);
		return ERR_PTR(ret);
	}

	return uobj;
}