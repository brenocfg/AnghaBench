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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct uverbs_method_def {int handler; unsigned int num_attrs; struct uverbs_attr_def*** attrs; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ access; } ;
struct TYPE_5__ {TYPE_1__ objs_arr; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ u2; } ;
struct uverbs_attr_def {TYPE_3__ attr; int /*<<< orphan*/  id; } ;
struct uverbs_api_object {int dummy; } ;
struct uverbs_api_ioctl_method {int driver_method; TYPE_3__ spec; int /*<<< orphan*/  handler; } ;
struct uverbs_api_attr {int driver_method; TYPE_3__ spec; int /*<<< orphan*/  handler; } ;
struct uverbs_api {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct uverbs_api_ioctl_method*) ; 
 int PTR_ERR (struct uverbs_api_ioctl_method*) ; 
 scalar_t__ UVERBS_ACCESS_DESTROY ; 
 scalar_t__ UVERBS_ACCESS_NEW ; 
 scalar_t__ UVERBS_ATTR_TYPE_ENUM_IN ; 
 scalar_t__ UVERBS_ATTR_TYPE_IDRS_ARRAY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int) ; 
 struct uverbs_api_ioctl_method* uapi_add_elm (struct uverbs_api*,int,int) ; 
 struct uverbs_api_ioctl_method* uapi_add_get_elm (struct uverbs_api*,int,int,int*) ; 
 int uapi_key_attr (int /*<<< orphan*/ ) ; 
 int uapi_key_ioctl_method (int /*<<< orphan*/ ) ; 
 int uverbs_destroy_def_handler ; 

__attribute__((used)) static int uapi_merge_method(struct uverbs_api *uapi,
			     struct uverbs_api_object *obj_elm, u32 obj_key,
			     const struct uverbs_method_def *method,
			     bool is_driver)
{
	u32 method_key = obj_key | uapi_key_ioctl_method(method->id);
	struct uverbs_api_ioctl_method *method_elm;
	unsigned int i;
	bool exists;

	if (!method->attrs)
		return 0;

	method_elm = uapi_add_get_elm(uapi, method_key, sizeof(*method_elm),
				      &exists);
	if (IS_ERR(method_elm))
		return PTR_ERR(method_elm);
	if (exists) {
		/*
		 * This occurs when a driver uses ADD_UVERBS_ATTRIBUTES_SIMPLE
		 */
		if (WARN_ON(method->handler))
			return -EINVAL;
	} else {
		WARN_ON(!method->handler);
		rcu_assign_pointer(method_elm->handler, method->handler);
		if (method->handler != uverbs_destroy_def_handler)
			method_elm->driver_method = is_driver;
	}

	for (i = 0; i != method->num_attrs; i++) {
		const struct uverbs_attr_def *attr = (*method->attrs)[i];
		struct uverbs_api_attr *attr_slot;

		if (!attr)
			continue;

		/*
		 * ENUM_IN contains the 'ids' pointer to the driver's .rodata,
		 * so if it is specified by a driver then it always makes this
		 * into a driver method.
		 */
		if (attr->attr.type == UVERBS_ATTR_TYPE_ENUM_IN)
			method_elm->driver_method |= is_driver;

		/*
		 * Like other uobject based things we only support a single
		 * uobject being NEW'd or DESTROY'd
		 */
		if (attr->attr.type == UVERBS_ATTR_TYPE_IDRS_ARRAY) {
			u8 access = attr->attr.u2.objs_arr.access;

			if (WARN_ON(access == UVERBS_ACCESS_NEW ||
				    access == UVERBS_ACCESS_DESTROY))
				return -EINVAL;
		}

		attr_slot =
			uapi_add_elm(uapi, method_key | uapi_key_attr(attr->id),
				     sizeof(*attr_slot));
		/* Attributes are not allowed to be modified by drivers */
		if (IS_ERR(attr_slot))
			return PTR_ERR(attr_slot);

		attr_slot->spec = attr->attr;
	}

	return 0;
}