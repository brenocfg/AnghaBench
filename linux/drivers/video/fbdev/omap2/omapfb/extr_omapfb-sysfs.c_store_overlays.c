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
struct omapfb_info {int num_overlays; int /*<<< orphan*/  region; struct omap_overlay** overlays; scalar_t__* rotation; struct omapfb2_device* fbdev; } ;
struct omapfb2_device {int num_overlays; int /*<<< orphan*/  dev; struct omap_overlay** overlays; } ;
struct omap_overlay {TYPE_1__* manager; int /*<<< orphan*/  id; } ;
struct fb_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* apply ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int OMAPFB_MAX_OVL_PER_FB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 struct omapfb_info* get_overlay_fb (struct omapfb2_device*,struct omap_overlay*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 int omapfb_apply_changes (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_lock (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_overlay_enable (struct omap_overlay*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_unlock (struct omapfb2_device*) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

__attribute__((used)) static ssize_t store_overlays(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct fb_info *fbi = dev_get_drvdata(dev);
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omap_overlay *ovls[OMAPFB_MAX_OVL_PER_FB];
	struct omap_overlay *ovl;
	int num_ovls, r, i;
	int len;
	bool added = false;

	num_ovls = 0;

	len = strlen(buf);
	if (buf[len - 1] == '\n')
		len = len - 1;

	lock_fb_info(fbi);
	omapfb_lock(fbdev);

	if (len > 0) {
		char *p = (char *)buf;
		int ovlnum;

		while (p < buf + len) {
			int found;
			if (num_ovls == OMAPFB_MAX_OVL_PER_FB) {
				r = -EINVAL;
				goto out;
			}

			ovlnum = simple_strtoul(p, &p, 0);
			if (ovlnum > fbdev->num_overlays) {
				r = -EINVAL;
				goto out;
			}

			found = 0;
			for (i = 0; i < num_ovls; ++i) {
				if (ovls[i] == fbdev->overlays[ovlnum]) {
					found = 1;
					break;
				}
			}

			if (!found)
				ovls[num_ovls++] = fbdev->overlays[ovlnum];

			p++;
		}
	}

	for (i = 0; i < num_ovls; ++i) {
		struct omapfb_info *ofbi2 = get_overlay_fb(fbdev, ovls[i]);
		if (ofbi2 && ofbi2 != ofbi) {
			dev_err(fbdev->dev, "overlay already in use\n");
			r = -EINVAL;
			goto out;
		}
	}

	/* detach unused overlays */
	for (i = 0; i < ofbi->num_overlays; ++i) {
		int t, found;

		ovl = ofbi->overlays[i];

		found = 0;

		for (t = 0; t < num_ovls; ++t) {
			if (ovl == ovls[t]) {
				found = 1;
				break;
			}
		}

		if (found)
			continue;

		DBG("detaching %d\n", ofbi->overlays[i]->id);

		omapfb_get_mem_region(ofbi->region);

		omapfb_overlay_enable(ovl, 0);

		if (ovl->manager)
			ovl->manager->apply(ovl->manager);

		omapfb_put_mem_region(ofbi->region);

		for (t = i + 1; t < ofbi->num_overlays; t++) {
			ofbi->rotation[t-1] = ofbi->rotation[t];
			ofbi->overlays[t-1] = ofbi->overlays[t];
		}

		ofbi->num_overlays--;
		i--;
	}

	for (i = 0; i < num_ovls; ++i) {
		int t, found;

		ovl = ovls[i];

		found = 0;

		for (t = 0; t < ofbi->num_overlays; ++t) {
			if (ovl == ofbi->overlays[t]) {
				found = 1;
				break;
			}
		}

		if (found)
			continue;
		ofbi->rotation[ofbi->num_overlays] = 0;
		ofbi->overlays[ofbi->num_overlays++] = ovl;

		added = true;
	}

	if (added) {
		omapfb_get_mem_region(ofbi->region);

		r = omapfb_apply_changes(fbi, 0);

		omapfb_put_mem_region(ofbi->region);

		if (r)
			goto out;
	}

	r = count;
out:
	omapfb_unlock(fbdev);
	unlock_fb_info(fbi);

	return r;
}