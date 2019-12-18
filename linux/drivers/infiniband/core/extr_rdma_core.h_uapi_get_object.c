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
typedef  scalar_t__ u16 ;
struct uverbs_api_object {int dummy; } ;
struct uverbs_api {int /*<<< orphan*/  radix; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMSG ; 
 struct uverbs_api_object const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ UVERBS_IDR_ANY_OBJECT ; 
 struct uverbs_api_object* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uapi_key_obj (scalar_t__) ; 

__attribute__((used)) static inline const struct uverbs_api_object *
uapi_get_object(struct uverbs_api *uapi, u16 object_id)
{
	const struct uverbs_api_object *res;

	if (object_id == UVERBS_IDR_ANY_OBJECT)
		return ERR_PTR(-ENOMSG);

	res = radix_tree_lookup(&uapi->radix, uapi_key_obj(object_id));
	if (!res)
		return ERR_PTR(-ENOENT);

	return res;
}