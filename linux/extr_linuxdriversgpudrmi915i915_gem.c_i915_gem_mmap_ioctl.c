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
typedef  scalar_t__ uint64_t ;
struct vm_area_struct {int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_3__ {int /*<<< orphan*/  filp; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  frontbuffer_ggtt_origin; TYPE_1__ base; } ;
struct drm_i915_gem_mmap {int flags; scalar_t__ addr_ptr; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 unsigned long ENOMEM ; 
 int ENXIO ; 
 int I915_MMAP_WC ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  ORIGIN_CPU ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86_FEATURE_PAT ; 
 scalar_t__ __vma_matches (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 
 unsigned long vm_mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
i915_gem_mmap_ioctl(struct drm_device *dev, void *data,
		    struct drm_file *file)
{
	struct drm_i915_gem_mmap *args = data;
	struct drm_i915_gem_object *obj;
	unsigned long addr;

	if (args->flags & ~(I915_MMAP_WC))
		return -EINVAL;

	if (args->flags & I915_MMAP_WC && !boot_cpu_has(X86_FEATURE_PAT))
		return -ENODEV;

	obj = i915_gem_object_lookup(file, args->handle);
	if (!obj)
		return -ENOENT;

	/* prime objects have no backing filp to GEM mmap
	 * pages from.
	 */
	if (!obj->base.filp) {
		i915_gem_object_put(obj);
		return -ENXIO;
	}

	addr = vm_mmap(obj->base.filp, 0, args->size,
		       PROT_READ | PROT_WRITE, MAP_SHARED,
		       args->offset);
	if (args->flags & I915_MMAP_WC) {
		struct mm_struct *mm = current->mm;
		struct vm_area_struct *vma;

		if (down_write_killable(&mm->mmap_sem)) {
			i915_gem_object_put(obj);
			return -EINTR;
		}
		vma = find_vma(mm, addr);
		if (vma && __vma_matches(vma, obj->base.filp, addr, args->size))
			vma->vm_page_prot =
				pgprot_writecombine(vm_get_page_prot(vma->vm_flags));
		else
			addr = -ENOMEM;
		up_write(&mm->mmap_sem);

		/* This may race, but that's ok, it only gets set */
		WRITE_ONCE(obj->frontbuffer_ggtt_origin, ORIGIN_CPU);
	}
	i915_gem_object_put(obj);
	if (IS_ERR((void *)addr))
		return addr;

	args->addr_ptr = (uint64_t) addr;

	return 0;
}