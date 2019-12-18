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
struct uverbs_objs_arr_attr {size_t len; int /*<<< orphan*/ * uobjects; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;
struct TYPE_4__ {TYPE_1__ objs_arr; } ;
struct uverbs_attr_spec {TYPE_2__ u2; } ;
struct uverbs_attr_bundle {int dummy; } ;
struct uverbs_api_attr {struct uverbs_attr_spec spec; } ;

/* Variables and functions */
 int uverbs_finalize_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct uverbs_attr_bundle*) ; 

__attribute__((used)) static int uverbs_free_idrs_array(const struct uverbs_api_attr *attr_uapi,
				  struct uverbs_objs_arr_attr *attr,
				  bool commit, struct uverbs_attr_bundle *attrs)
{
	const struct uverbs_attr_spec *spec = &attr_uapi->spec;
	int current_ret;
	int ret = 0;
	size_t i;

	for (i = 0; i != attr->len; i++) {
		current_ret = uverbs_finalize_object(attr->uobjects[i],
						     spec->u2.objs_arr.access,
						     commit, attrs);
		if (!ret)
			ret = current_ret;
	}

	return ret;
}