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
struct fb_info {int node; } ;
struct TYPE_2__ {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int* con2fb_map ; 
 int con2fb_release_oldinfo (int /*<<< orphan*/ ,struct fb_info*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbcon_has_console_bind ; 
 int /*<<< orphan*/  fbcon_unbind () ; 
 int first_fb_vc ; 
 int last_fb_vc ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  search_fb_in_map (int) ; 
 int /*<<< orphan*/  set_con2fb_map (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* vc_cons ; 

void fbcon_fb_unbind(struct fb_info *info)
{
	int i, new_idx = -1, ret = 0;
	int idx = info->node;

	WARN_CONSOLE_UNLOCKED();

	if (!fbcon_has_console_bind)
		return;

	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		if (con2fb_map[i] != idx &&
		    con2fb_map[i] != -1) {
			new_idx = con2fb_map[i];
			break;
		}
	}

	if (new_idx != -1) {
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map[i] == idx)
				set_con2fb_map(i, new_idx, 0);
		}
	} else {
		struct fb_info *info = registered_fb[idx];

		/* This is sort of like set_con2fb_map, except it maps
		 * the consoles to no device and then releases the
		 * oldinfo to free memory and cancel the cursor blink
		 * timer. I can imagine this just becoming part of
		 * set_con2fb_map where new_idx is -1
		 */
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map[i] == idx) {
				con2fb_map[i] = -1;
				if (!search_fb_in_map(idx)) {
					ret = con2fb_release_oldinfo(vc_cons[i].d,
								     info, NULL, i,
								     idx, 0);
					if (ret) {
						con2fb_map[i] = idx;
						return;
					}
				}
			}
		}
		fbcon_unbind();
	}
}