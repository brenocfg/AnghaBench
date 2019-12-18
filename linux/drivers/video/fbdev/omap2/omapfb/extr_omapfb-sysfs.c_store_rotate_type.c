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
struct omapfb_info {int rotation_type; int /*<<< orphan*/  region; } ;
struct omapfb2_mem_region {scalar_t__ size; } ;
struct fb_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int OMAP_DSS_ROT_DMA ; 
 int OMAP_DSS_ROT_VRFB ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 struct omapfb2_mem_region* omapfb_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (struct omapfb2_mem_region*) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

__attribute__((used)) static ssize_t store_rotate_type(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct fb_info *fbi = dev_get_drvdata(dev);
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_mem_region *rg;
	int rot_type;
	int r;

	r = kstrtoint(buf, 0, &rot_type);
	if (r)
		return r;

	if (rot_type != OMAP_DSS_ROT_DMA && rot_type != OMAP_DSS_ROT_VRFB)
		return -EINVAL;

	lock_fb_info(fbi);

	r = 0;
	if (rot_type == ofbi->rotation_type)
		goto out;

	rg = omapfb_get_mem_region(ofbi->region);

	if (rg->size) {
		r = -EBUSY;
		goto put_region;
	}

	ofbi->rotation_type = rot_type;

	/*
	 * Since the VRAM for this FB is not allocated at the moment we don't
	 * need to do any further parameter checking at this point.
	 */
put_region:
	omapfb_put_mem_region(rg);
out:
	unlock_fb_info(fbi);

	return r ? r : count;
}