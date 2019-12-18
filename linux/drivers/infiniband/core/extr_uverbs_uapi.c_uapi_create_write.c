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
typedef  int /*<<< orphan*/  u32 ;
struct uverbs_api_write_method {scalar_t__ is_ex; int disabled; int /*<<< orphan*/  resp_size; int /*<<< orphan*/  req_size; int /*<<< orphan*/  has_resp; int /*<<< orphan*/  has_udata; scalar_t__ handler; } ;
struct uverbs_api {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_ex; int /*<<< orphan*/  resp_size; int /*<<< orphan*/  req_size; int /*<<< orphan*/  has_resp; int /*<<< orphan*/  has_udata; int /*<<< orphan*/  command_num; } ;
struct uapi_definition {TYPE_1__ write; scalar_t__ func_write; } ;
struct ib_device {int uverbs_ex_cmd_mask; int uverbs_cmd_mask; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct uverbs_api_write_method*) ; 
 int PTR_ERR (struct uverbs_api_write_method*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct uverbs_api_write_method* uapi_add_get_elm (struct uverbs_api*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  uapi_key_write_ex_method (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uapi_key_write_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uapi_create_write(struct uverbs_api *uapi,
			     struct ib_device *ibdev,
			     const struct uapi_definition *def,
			     u32 obj_key,
			     u32 *cur_method_key)
{
	struct uverbs_api_write_method *method_elm;
	u32 method_key = obj_key;
	bool exists;

	if (def->write.is_ex)
		method_key |= uapi_key_write_ex_method(def->write.command_num);
	else
		method_key |= uapi_key_write_method(def->write.command_num);

	method_elm = uapi_add_get_elm(uapi, method_key, sizeof(*method_elm),
				      &exists);
	if (IS_ERR(method_elm))
		return PTR_ERR(method_elm);

	if (WARN_ON(exists && (def->write.is_ex != method_elm->is_ex)))
		return -EINVAL;

	method_elm->is_ex = def->write.is_ex;
	method_elm->handler = def->func_write;
	if (def->write.is_ex)
		method_elm->disabled = !(ibdev->uverbs_ex_cmd_mask &
					 BIT_ULL(def->write.command_num));
	else
		method_elm->disabled = !(ibdev->uverbs_cmd_mask &
					 BIT_ULL(def->write.command_num));

	if (!def->write.is_ex && def->func_write) {
		method_elm->has_udata = def->write.has_udata;
		method_elm->has_resp = def->write.has_resp;
		method_elm->req_size = def->write.req_size;
		method_elm->resp_size = def->write.resp_size;
	}

	*cur_method_key = method_key;
	return 0;
}