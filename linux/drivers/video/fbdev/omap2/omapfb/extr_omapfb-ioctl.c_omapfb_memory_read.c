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
struct omapfb_memory_read {int buffer_size; int w; int h; int /*<<< orphan*/  buffer; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct omap_dss_device {TYPE_1__* driver; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {int (* memory_read ) (struct omap_dss_device*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,void*,int) ; 
 struct omap_dss_device* fb2display (struct fb_info*) ; 
 int stub1 (struct omap_dss_device*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static int omapfb_memory_read(struct fb_info *fbi,
		struct omapfb_memory_read *mr)
{
	struct omap_dss_device *display = fb2display(fbi);
	void *buf;
	int r;

	if (!display || !display->driver->memory_read)
		return -ENOENT;

	if (!access_ok(mr->buffer, mr->buffer_size))
		return -EFAULT;

	if (mr->w > 4096 || mr->h > 4096)
		return -EINVAL;

	if (mr->w * mr->h * 3 > mr->buffer_size)
		return -EINVAL;

	buf = vmalloc(mr->buffer_size);
	if (!buf) {
		DBG("vmalloc failed\n");
		return -ENOMEM;
	}

	r = display->driver->memory_read(display, buf, mr->buffer_size,
			mr->x, mr->y, mr->w, mr->h);

	if (r > 0) {
		if (copy_to_user(mr->buffer, buf, r))
			r = -EFAULT;
	}

	vfree(buf);

	return r;
}