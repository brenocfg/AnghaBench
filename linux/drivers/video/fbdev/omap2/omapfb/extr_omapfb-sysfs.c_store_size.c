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
struct omapfb_info {int num_overlays; struct omapfb2_mem_region* region; struct omap_overlay** overlays; struct omapfb2_device* fbdev; } ;
struct omapfb2_mem_region {unsigned long size; int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_count; int /*<<< orphan*/  type; int /*<<< orphan*/  map_count; int /*<<< orphan*/  id; } ;
struct omapfb2_device {int num_fbs; struct fb_info** fbs; } ;
struct omap_overlay {scalar_t__ (* is_enabled ) (struct omap_overlay*) ;} ;
struct omap_dss_device {TYPE_1__* driver; } ;
struct fb_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct omap_dss_device* fb2display (struct fb_info*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 int omapfb_realloc_fbmem (struct fb_info*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 scalar_t__ stub2 (struct omap_overlay*) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_size(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct fb_info *fbi = dev_get_drvdata(dev);
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omap_dss_device *display = fb2display(fbi);
	struct omapfb2_mem_region *rg;
	unsigned long size;
	int r;
	int i;

	r = kstrtoul(buf, 0, &size);
	if (r)
		return r;

	size = PAGE_ALIGN(size);

	lock_fb_info(fbi);

	if (display && display->driver->sync)
		display->driver->sync(display);

	rg = ofbi->region;

	down_write_nested(&rg->lock, rg->id);
	atomic_inc(&rg->lock_count);

	if (atomic_read(&rg->map_count)) {
		r = -EBUSY;
		goto out;
	}

	for (i = 0; i < fbdev->num_fbs; i++) {
		struct omapfb_info *ofbi2 = FB2OFB(fbdev->fbs[i]);
		int j;

		if (ofbi2->region != rg)
			continue;

		for (j = 0; j < ofbi2->num_overlays; j++) {
			struct omap_overlay *ovl;
			ovl = ofbi2->overlays[j];
			if (ovl->is_enabled(ovl)) {
				r = -EBUSY;
				goto out;
			}
		}
	}

	if (size != ofbi->region->size) {
		r = omapfb_realloc_fbmem(fbi, size, ofbi->region->type);
		if (r) {
			dev_err(dev, "realloc fbmem failed\n");
			goto out;
		}
	}

	r = count;
out:
	atomic_dec(&rg->lock_count);
	up_write(&rg->lock);

	unlock_fb_info(fbi);

	return r;
}