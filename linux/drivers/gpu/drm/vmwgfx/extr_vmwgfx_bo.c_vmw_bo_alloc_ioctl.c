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
struct drm_vmw_dmabuf_rep {scalar_t__ cur_gmr_offset; void* cur_gmr_id; int /*<<< orphan*/  map_handle; void* handle; } ;
struct drm_vmw_alloc_dmabuf_req {int /*<<< orphan*/  size; } ;
union drm_vmw_alloc_dmabuf_arg {struct drm_vmw_dmabuf_rep rep; struct drm_vmw_alloc_dmabuf_req req; } ;
typedef  void* uint32_t ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct TYPE_4__ {int /*<<< orphan*/  vma_node; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct vmw_buffer_object {TYPE_2__ base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 TYPE_3__* vmw_fpriv (struct drm_file*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int vmw_user_bo_alloc (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,struct vmw_buffer_object**,int /*<<< orphan*/ *) ; 

int vmw_bo_alloc_ioctl(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	union drm_vmw_alloc_dmabuf_arg *arg =
	    (union drm_vmw_alloc_dmabuf_arg *)data;
	struct drm_vmw_alloc_dmabuf_req *req = &arg->req;
	struct drm_vmw_dmabuf_rep *rep = &arg->rep;
	struct vmw_buffer_object *vbo;
	uint32_t handle;
	int ret;

	ret = ttm_read_lock(&dev_priv->reservation_sem, true);
	if (unlikely(ret != 0))
		return ret;

	ret = vmw_user_bo_alloc(dev_priv, vmw_fpriv(file_priv)->tfile,
				req->size, false, &handle, &vbo,
				NULL);
	if (unlikely(ret != 0))
		goto out_no_bo;

	rep->handle = handle;
	rep->map_handle = drm_vma_node_offset_addr(&vbo->base.base.vma_node);
	rep->cur_gmr_id = handle;
	rep->cur_gmr_offset = 0;

	vmw_bo_unreference(&vbo);

out_no_bo:
	ttm_read_unlock(&dev_priv->reservation_sem);

	return ret;
}