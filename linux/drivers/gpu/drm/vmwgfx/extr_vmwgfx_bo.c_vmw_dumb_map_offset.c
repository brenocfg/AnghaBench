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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  vma_node; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct vmw_buffer_object {TYPE_2__ base; } ;
struct ttm_object_file {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 TYPE_3__* vmw_fpriv (struct drm_file*) ; 
 int vmw_user_bo_lookup (struct ttm_object_file*,int /*<<< orphan*/ ,struct vmw_buffer_object**,int /*<<< orphan*/ *) ; 

int vmw_dumb_map_offset(struct drm_file *file_priv,
			struct drm_device *dev, uint32_t handle,
			uint64_t *offset)
{
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct vmw_buffer_object *out_buf;
	int ret;

	ret = vmw_user_bo_lookup(tfile, handle, &out_buf, NULL);
	if (ret != 0)
		return -EINVAL;

	*offset = drm_vma_node_offset_addr(&out_buf->base.base.vma_node);
	vmw_bo_unreference(&out_buf);
	return 0;
}