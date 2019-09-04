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
typedef  int /*<<< orphan*/  u16 ;
struct uverbs_api_object {int dummy; } ;
struct ib_uverbs_file {TYPE_1__* device; } ;
struct ib_uobject {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum uverbs_obj_access { ____Placeholder_uverbs_obj_access } uverbs_obj_access ;
struct TYPE_2__ {int /*<<< orphan*/  uapi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_uobject* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  UVERBS_ACCESS_DESTROY 131 
#define  UVERBS_ACCESS_NEW 130 
#define  UVERBS_ACCESS_READ 129 
#define  UVERBS_ACCESS_WRITE 128 
 int /*<<< orphan*/  UVERBS_LOOKUP_DESTROY ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_READ ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ib_uobject* rdma_alloc_begin_uobject (struct uverbs_api_object const*,struct ib_uverbs_file*) ; 
 struct ib_uobject* rdma_lookup_get_uobject (struct uverbs_api_object const*,struct ib_uverbs_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uverbs_api_object* uapi_get_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ib_uobject *
uverbs_get_uobject_from_file(u16 object_id,
			     struct ib_uverbs_file *ufile,
			     enum uverbs_obj_access access, s64 id)
{
	const struct uverbs_api_object *obj =
		uapi_get_object(ufile->device->uapi, object_id);

	switch (access) {
	case UVERBS_ACCESS_READ:
		return rdma_lookup_get_uobject(obj, ufile, id,
					       UVERBS_LOOKUP_READ);
	case UVERBS_ACCESS_DESTROY:
		/* Actual destruction is done inside uverbs_handle_method */
		return rdma_lookup_get_uobject(obj, ufile, id,
					       UVERBS_LOOKUP_DESTROY);
	case UVERBS_ACCESS_WRITE:
		return rdma_lookup_get_uobject(obj, ufile, id,
					       UVERBS_LOOKUP_WRITE);
	case UVERBS_ACCESS_NEW:
		return rdma_alloc_begin_uobject(obj, ufile);
	default:
		WARN_ON(true);
		return ERR_PTR(-EOPNOTSUPP);
	}
}