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
struct gtt_range {int /*<<< orphan*/  gem; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 struct gtt_range* psb_gtt_alloc_range (struct drm_device*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gtt_range *psbfb_alloc(struct drm_device *dev, int aligned_size)
{
	struct gtt_range *backing;
	/* Begin by trying to use stolen memory backing */
	backing = psb_gtt_alloc_range(dev, aligned_size, "fb", 1, PAGE_SIZE);
	if (backing) {
		drm_gem_private_object_init(dev, &backing->gem, aligned_size);
		return backing;
	}
	return NULL;
}