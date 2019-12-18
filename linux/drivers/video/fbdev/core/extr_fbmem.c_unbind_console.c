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
struct fb_info {int node; } ;

/* Variables and functions */
 int FB_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fbcon_fb_unbind (struct fb_info*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

__attribute__((used)) static void unbind_console(struct fb_info *fb_info)
{
	int i = fb_info->node;

	if (WARN_ON(i < 0 || i >= FB_MAX || registered_fb[i] != fb_info))
		return;

	console_lock();
	lock_fb_info(fb_info);
	fbcon_fb_unbind(fb_info);
	unlock_fb_info(fb_info);
	console_unlock();
}