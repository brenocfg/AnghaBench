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
struct TYPE_2__ {int region_cnt; } ;
struct omapfb_device {int /*<<< orphan*/ ** fb_info; TYPE_1__ mem_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbinfo_cleanup (struct omapfb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void planes_cleanup(struct omapfb_device *fbdev)
{
	int i;

	for (i = 0; i < fbdev->mem_desc.region_cnt; i++) {
		if (fbdev->fb_info[i] == NULL)
			break;
		fbinfo_cleanup(fbdev, fbdev->fb_info[i]);
		framebuffer_release(fbdev->fb_info[i]);
	}
}