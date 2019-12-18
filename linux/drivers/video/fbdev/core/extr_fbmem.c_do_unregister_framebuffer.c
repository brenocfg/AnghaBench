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
struct TYPE_2__ {int flags; scalar_t__ addr; } ;
struct fb_info {size_t node; int /*<<< orphan*/  modelist; TYPE_1__ pixmap; } ;
struct fb_event {struct fb_info* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_EVENT_FB_UNREGISTERED ; 
 int FB_PIXMAP_DEFAULT ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fb_cleanup_device (struct fb_info*) ; 
 int /*<<< orphan*/  fb_destroy_modelist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_notifier_call_chain (int /*<<< orphan*/ ,struct fb_event*) ; 
 int /*<<< orphan*/  fbcon_fb_unregistered (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  num_registered_fb ; 
 int /*<<< orphan*/  put_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/ ** registered_fb ; 
 int /*<<< orphan*/  unlink_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void do_unregister_framebuffer(struct fb_info *fb_info)
{
	unlink_framebuffer(fb_info);
	if (fb_info->pixmap.addr &&
	    (fb_info->pixmap.flags & FB_PIXMAP_DEFAULT))
		kfree(fb_info->pixmap.addr);
	fb_destroy_modelist(&fb_info->modelist);
	registered_fb[fb_info->node] = NULL;
	num_registered_fb--;
	fb_cleanup_device(fb_info);
#ifdef CONFIG_GUMSTIX_AM200EPD
	{
		struct fb_event event;
		event.info = fb_info;
		fb_notifier_call_chain(FB_EVENT_FB_UNREGISTERED, &event);
	}
#endif
	console_lock();
	fbcon_fb_unregistered(fb_info);
	console_unlock();

	/* this may free fb info */
	put_fb_info(fb_info);
}