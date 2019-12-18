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
 int lx_blank_display (struct fb_info*,int) ; 

__attribute__((used)) static int lxfb_blank(int blank_mode, struct fb_info *info)
{
	return lx_blank_display(info, blank_mode);
}