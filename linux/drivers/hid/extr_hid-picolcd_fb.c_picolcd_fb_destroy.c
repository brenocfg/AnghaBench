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
typedef  int /*<<< orphan*/  u8 ;
struct picolcd_fb_data {int /*<<< orphan*/ * picolcd; } ;
struct TYPE_2__ {scalar_t__ smem_start; } ;
struct fb_info {TYPE_1__ fix; struct picolcd_fb_data* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void picolcd_fb_destroy(struct fb_info *info)
{
	struct picolcd_fb_data *fbdata = info->par;

	/* make sure no work is deferred */
	fb_deferred_io_cleanup(info);

	/* No thridparty should ever unregister our framebuffer! */
	WARN_ON(fbdata->picolcd != NULL);

	vfree((u8 *)info->fix.smem_start);
	framebuffer_release(info);
}