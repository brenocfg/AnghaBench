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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_user_resource_conv {scalar_t__ object_type; struct vmw_resource* (* base_obj_to_res ) (struct ttm_base_object*) ;} ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;
struct ttm_object_file {int dummy; } ;
struct ttm_base_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct vmw_resource* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 struct vmw_resource* stub1 (struct ttm_base_object*) ; 
 struct ttm_base_object* ttm_base_object_noref_lookup (struct ttm_object_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_base_object_noref_release () ; 
 scalar_t__ ttm_base_object_type (struct ttm_base_object*) ; 
 scalar_t__ unlikely (int) ; 

struct vmw_resource *
vmw_user_resource_noref_lookup_handle(struct vmw_private *dev_priv,
				      struct ttm_object_file *tfile,
				      uint32_t handle,
				      const struct vmw_user_resource_conv
				      *converter)
{
	struct ttm_base_object *base;

	base = ttm_base_object_noref_lookup(tfile, handle);
	if (!base)
		return ERR_PTR(-ESRCH);

	if (unlikely(ttm_base_object_type(base) != converter->object_type)) {
		ttm_base_object_noref_release();
		return ERR_PTR(-EINVAL);
	}

	return converter->base_obj_to_res(base);
}