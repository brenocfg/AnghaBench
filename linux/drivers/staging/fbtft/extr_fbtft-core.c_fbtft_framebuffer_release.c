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
struct fb_info {int /*<<< orphan*/  screen_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void fbtft_framebuffer_release(struct fb_info *info)
{
	fb_deferred_io_cleanup(info);
	vfree(info->screen_buffer);
	framebuffer_release(info);
}