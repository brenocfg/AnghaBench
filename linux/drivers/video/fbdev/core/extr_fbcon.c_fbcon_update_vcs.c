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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbcon_modechanged (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_set_all_vcs (struct fb_info*) ; 

void fbcon_update_vcs(struct fb_info *info, bool all)
{
	if (all)
		fbcon_set_all_vcs(info);
	else
		fbcon_modechanged(info);
}