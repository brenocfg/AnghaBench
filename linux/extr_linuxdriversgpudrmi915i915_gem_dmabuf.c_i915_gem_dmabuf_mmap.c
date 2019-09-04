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
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_file; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  filp; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int call_mmap (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 struct drm_i915_gem_object* dma_buf_to_obj (struct dma_buf*) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_gem_dmabuf_mmap(struct dma_buf *dma_buf, struct vm_area_struct *vma)
{
	struct drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	int ret;

	if (obj->base.size < vma->vm_end - vma->vm_start)
		return -EINVAL;

	if (!obj->base.filp)
		return -ENODEV;

	ret = call_mmap(obj->base.filp, vma);
	if (ret)
		return ret;

	fput(vma->vm_file);
	vma->vm_file = get_file(obj->base.filp);

	return 0;
}