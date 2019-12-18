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
struct uverbs_attr_bundle {int dummy; } ;
struct uverbs_api_object {int dummy; } ;
struct ib_uobject {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int PTR_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_WRITE ; 
 struct ib_uobject* __uobj_get_destroy (struct uverbs_api_object const*,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  rdma_lookup_put_uobject (struct ib_uobject*,int /*<<< orphan*/ ) ; 

int __uobj_perform_destroy(const struct uverbs_api_object *obj, u32 id,
			   struct uverbs_attr_bundle *attrs)
{
	struct ib_uobject *uobj;

	uobj = __uobj_get_destroy(obj, id, attrs);
	if (IS_ERR(uobj))
		return PTR_ERR(uobj);

	rdma_lookup_put_uobject(uobj, UVERBS_LOOKUP_WRITE);
	return 0;
}