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
struct fb_tilecursor {int dummy; } ;
struct fb_info {struct arkfb_info* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  vgabase; } ;
struct arkfb_info {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  svga_tilecursor (int /*<<< orphan*/ ,struct fb_info*,struct fb_tilecursor*) ; 

__attribute__((used)) static void arkfb_tilecursor(struct fb_info *info, struct fb_tilecursor *cursor)
{
	struct arkfb_info *par = info->par;

	svga_tilecursor(par->state.vgabase, info, cursor);
}