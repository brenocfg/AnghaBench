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
 int /*<<< orphan*/  hga_clear_screen () ; 
 int /*<<< orphan*/  hga_gfx_mode () ; 
 int /*<<< orphan*/  hga_show_logo (struct fb_info*) ; 
 int /*<<< orphan*/  nologo ; 

__attribute__((used)) static int hgafb_open(struct fb_info *info, int init)
{
	hga_gfx_mode();
	hga_clear_screen();
	if (!nologo) hga_show_logo(info);
	return 0;
}