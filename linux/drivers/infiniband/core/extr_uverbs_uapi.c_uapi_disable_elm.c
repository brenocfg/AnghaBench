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
struct uverbs_api_write_method {int disabled; } ;
struct uverbs_api_object {int disabled; } ;
struct uverbs_api_ioctl_method {int disabled; } ;
struct uverbs_api {int dummy; } ;
struct uapi_definition {scalar_t__ scope; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct uverbs_api_write_method*) ; 
 int PTR_ERR (struct uverbs_api_write_method*) ; 
 scalar_t__ UAPI_SCOPE_METHOD ; 
 scalar_t__ UAPI_SCOPE_OBJECT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct uverbs_api_write_method* uapi_add_get_elm (struct uverbs_api*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ uapi_key_is_ioctl_method (int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_write_ex_method (int /*<<< orphan*/ ) ; 
 scalar_t__ uapi_key_is_write_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uapi_disable_elm(struct uverbs_api *uapi,
			    const struct uapi_definition *def,
			    u32 obj_key,
			    u32 method_key)
{
	bool exists;

	if (def->scope == UAPI_SCOPE_OBJECT) {
		struct uverbs_api_object *obj_elm;

		obj_elm = uapi_add_get_elm(
			uapi, obj_key, sizeof(*obj_elm), &exists);
		if (IS_ERR(obj_elm))
			return PTR_ERR(obj_elm);
		obj_elm->disabled = 1;
		return 0;
	}

	if (def->scope == UAPI_SCOPE_METHOD &&
	    uapi_key_is_ioctl_method(method_key)) {
		struct uverbs_api_ioctl_method *method_elm;

		method_elm = uapi_add_get_elm(uapi, method_key,
					      sizeof(*method_elm), &exists);
		if (IS_ERR(method_elm))
			return PTR_ERR(method_elm);
		method_elm->disabled = 1;
		return 0;
	}

	if (def->scope == UAPI_SCOPE_METHOD &&
	    (uapi_key_is_write_method(method_key) ||
	     uapi_key_is_write_ex_method(method_key))) {
		struct uverbs_api_write_method *write_elm;

		write_elm = uapi_add_get_elm(uapi, method_key,
					     sizeof(*write_elm), &exists);
		if (IS_ERR(write_elm))
			return PTR_ERR(write_elm);
		write_elm->disabled = 1;
		return 0;
	}

	WARN_ON(true);
	return -EINVAL;
}