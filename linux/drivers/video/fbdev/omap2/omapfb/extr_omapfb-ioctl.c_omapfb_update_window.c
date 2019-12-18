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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct omap_dss_device {TYPE_1__* driver; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {int (* update ) (struct omap_dss_device*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* get_resolution ) (struct omap_dss_device*,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct omap_dss_device* fb2display (struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,scalar_t__*,scalar_t__*) ; 
 int stub2 (struct omap_dss_device*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int omapfb_update_window(struct fb_info *fbi,
		u32 x, u32 y, u32 w, u32 h)
{
	struct omap_dss_device *display = fb2display(fbi);
	u16 dw, dh;

	if (!display)
		return 0;

	if (w == 0 || h == 0)
		return 0;

	display->driver->get_resolution(display, &dw, &dh);

	if (x + w > dw || y + h > dh)
		return -EINVAL;

	return display->driver->update(display, x, y, w, h);
}