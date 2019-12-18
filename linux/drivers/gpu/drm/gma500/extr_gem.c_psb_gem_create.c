#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {TYPE_1__* filp; } ;
struct gtt_range {TYPE_2__ gem; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_DMA32 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,TYPE_2__*,...) ; 
 int drm_gem_handle_create (struct drm_file*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_gem_object_init (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_gem_object_release (TYPE_2__*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int) ; 
 struct gtt_range* psb_gtt_alloc_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_gtt_free_range (struct drm_device*,struct gtt_range*) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int psb_gem_create(struct drm_file *file, struct drm_device *dev, u64 size,
		   u32 *handlep, int stolen, u32 align)
{
	struct gtt_range *r;
	int ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);

	/* Allocate our object - for now a direct gtt range which is not
	   stolen memory backed */
	r = psb_gtt_alloc_range(dev, size, "gem", 0, PAGE_SIZE);
	if (r == NULL) {
		dev_err(dev->dev, "no memory for %lld byte GEM object\n", size);
		return -ENOSPC;
	}
	/* Initialize the extra goodies GEM needs to do all the hard work */
	if (drm_gem_object_init(dev, &r->gem, size) != 0) {
		psb_gtt_free_range(dev, r);
		/* GEM doesn't give an error code so use -ENOMEM */
		dev_err(dev->dev, "GEM init failed for %lld\n", size);
		return -ENOMEM;
	}
	/* Limit the object to 32bit mappings */
	mapping_set_gfp_mask(r->gem.filp->f_mapping, GFP_KERNEL | __GFP_DMA32);
	/* Give the object a handle so we can carry it more easily */
	ret = drm_gem_handle_create(file, &r->gem, &handle);
	if (ret) {
		dev_err(dev->dev, "GEM handle failed for %p, %lld\n",
							&r->gem, size);
		drm_gem_object_release(&r->gem);
		psb_gtt_free_range(dev, r);
		return ret;
	}
	/* We have the initial and handle reference but need only one now */
	drm_gem_object_put_unlocked(&r->gem);
	*handlep = handle;
	return 0;
}