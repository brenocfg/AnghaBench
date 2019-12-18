#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  obj_type; } ;
struct TYPE_8__ {TYPE_3__ objs_arr; } ;
struct TYPE_5__ {int /*<<< orphan*/  obj_type; } ;
struct TYPE_6__ {TYPE_1__ obj; } ;
struct uverbs_attr_spec {scalar_t__ type; TYPE_4__ u2; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVERBS_API_KEY_ERR ; 
 scalar_t__ UVERBS_ATTR_TYPE_FD ; 
 scalar_t__ UVERBS_ATTR_TYPE_IDR ; 
 scalar_t__ UVERBS_ATTR_TYPE_IDRS_ARRAY ; 

__attribute__((used)) static u32 uapi_get_obj_id(struct uverbs_attr_spec *spec)
{
	if (spec->type == UVERBS_ATTR_TYPE_IDR ||
	    spec->type == UVERBS_ATTR_TYPE_FD)
		return spec->u.obj.obj_type;
	if (spec->type == UVERBS_ATTR_TYPE_IDRS_ARRAY)
		return spec->u2.objs_arr.obj_type;
	return UVERBS_API_KEY_ERR;
}