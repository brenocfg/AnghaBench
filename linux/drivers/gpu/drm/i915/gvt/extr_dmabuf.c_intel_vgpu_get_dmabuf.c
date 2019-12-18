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
struct intel_vgpu_dmabuf_obj {int initref; int /*<<< orphan*/  kref; int /*<<< orphan*/  dmabuf_id; int /*<<< orphan*/  info; } ;
struct intel_vgpu {int /*<<< orphan*/  dmabuf_lock; int /*<<< orphan*/  id; TYPE_2__* gvt; } ;
struct TYPE_6__ {int /*<<< orphan*/  refcount; } ;
struct drm_i915_gem_object {TYPE_3__ base; int /*<<< orphan*/  gvt_info; } ;
struct drm_device {int dummy; } ;
struct dma_buf {int /*<<< orphan*/  file; } ;
struct TYPE_5__ {TYPE_1__* dev_priv; } ;
struct TYPE_4__ {struct drm_device drm; } ;

/* Variables and functions */
 int DRM_CLOEXEC ; 
 int DRM_RDWR ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 int PTR_ERR (struct dma_buf*) ; 
 int dma_buf_fd (struct dma_buf*,int) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dmabuf_obj_get (struct intel_vgpu_dmabuf_obj*) ; 
 int /*<<< orphan*/  dmabuf_obj_put (struct intel_vgpu_dmabuf_obj*) ; 
 int /*<<< orphan*/  file_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_dpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,...) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 struct dma_buf* i915_gem_prime_export (TYPE_3__*,int) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct intel_vgpu_dmabuf_obj* pick_dmabuf_by_num (struct intel_vgpu*,unsigned int) ; 
 struct drm_i915_gem_object* vgpu_create_gem (struct drm_device*,int /*<<< orphan*/ ) ; 

int intel_vgpu_get_dmabuf(struct intel_vgpu *vgpu, unsigned int dmabuf_id)
{
	struct drm_device *dev = &vgpu->gvt->dev_priv->drm;
	struct intel_vgpu_dmabuf_obj *dmabuf_obj;
	struct drm_i915_gem_object *obj;
	struct dma_buf *dmabuf;
	int dmabuf_fd;
	int ret = 0;

	mutex_lock(&vgpu->dmabuf_lock);

	dmabuf_obj = pick_dmabuf_by_num(vgpu, dmabuf_id);
	if (dmabuf_obj == NULL) {
		gvt_vgpu_err("invalid dmabuf id:%d\n", dmabuf_id);
		ret = -EINVAL;
		goto out;
	}

	obj = vgpu_create_gem(dev, dmabuf_obj->info);
	if (obj == NULL) {
		gvt_vgpu_err("create gvt gem obj failed\n");
		ret = -ENOMEM;
		goto out;
	}

	obj->gvt_info = dmabuf_obj->info;

	dmabuf = i915_gem_prime_export(&obj->base, DRM_CLOEXEC | DRM_RDWR);
	if (IS_ERR(dmabuf)) {
		gvt_vgpu_err("export dma-buf failed\n");
		ret = PTR_ERR(dmabuf);
		goto out_free_gem;
	}

	i915_gem_object_put(obj);

	ret = dma_buf_fd(dmabuf, DRM_CLOEXEC | DRM_RDWR);
	if (ret < 0) {
		gvt_vgpu_err("create dma-buf fd failed ret:%d\n", ret);
		goto out_free_dmabuf;
	}
	dmabuf_fd = ret;

	dmabuf_obj_get(dmabuf_obj);

	if (dmabuf_obj->initref) {
		dmabuf_obj->initref = false;
		dmabuf_obj_put(dmabuf_obj);
	}

	mutex_unlock(&vgpu->dmabuf_lock);

	gvt_dbg_dpy("vgpu%d: dmabuf:%d, dmabuf ref %d, fd:%d\n"
		    "        file count: %ld, GEM ref: %d\n",
		    vgpu->id, dmabuf_obj->dmabuf_id,
		    kref_read(&dmabuf_obj->kref),
		    dmabuf_fd,
		    file_count(dmabuf->file),
		    kref_read(&obj->base.refcount));

	return dmabuf_fd;

out_free_dmabuf:
	dma_buf_put(dmabuf);
out_free_gem:
	i915_gem_object_put(obj);
out:
	mutex_unlock(&vgpu->dmabuf_lock);
	return ret;
}