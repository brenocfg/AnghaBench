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
struct vm_area_struct {int dummy; } ;
struct drm_gem_object {int /*<<< orphan*/  size; } ;
struct dma_buf {struct drm_gem_object* priv; } ;

/* Variables and functions */
 int __tegra_gem_mmap (struct drm_gem_object*,struct vm_area_struct*) ; 
 int drm_gem_mmap_obj (struct drm_gem_object*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int tegra_gem_prime_mmap(struct dma_buf *buf, struct vm_area_struct *vma)
{
	struct drm_gem_object *gem = buf->priv;
	int err;

	err = drm_gem_mmap_obj(gem, gem->size, vma);
	if (err < 0)
		return err;

	return __tegra_gem_mmap(gem, vma);
}