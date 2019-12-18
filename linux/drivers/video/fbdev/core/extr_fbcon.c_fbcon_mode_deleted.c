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
struct fbcon_display {int /*<<< orphan*/  mode; } ;
struct fb_videomode {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int* con2fb_map ; 
 struct fbcon_display* fb_display ; 
 scalar_t__ fb_mode_is_equal (int /*<<< orphan*/ ,struct fb_videomode*) ; 
 int first_fb_vc ; 
 int last_fb_vc ; 
 struct fb_info** registered_fb ; 

int fbcon_mode_deleted(struct fb_info *info,
		       struct fb_videomode *mode)
{
	struct fb_info *fb_info;
	struct fbcon_display *p;
	int i, j, found = 0;

	/* before deletion, ensure that mode is not in use */
	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		j = con2fb_map[i];
		if (j == -1)
			continue;
		fb_info = registered_fb[j];
		if (fb_info != info)
			continue;
		p = &fb_display[i];
		if (!p || !p->mode)
			continue;
		if (fb_mode_is_equal(p->mode, mode)) {
			found = 1;
			break;
		}
	}
	return found;
}