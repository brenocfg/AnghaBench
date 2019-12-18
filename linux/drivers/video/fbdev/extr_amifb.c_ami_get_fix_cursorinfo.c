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
struct fb_fix_cursorinfo {int crsr_color1; int crsr_color2; int /*<<< orphan*/  crsr_ysize; int /*<<< orphan*/  crsr_height; int /*<<< orphan*/  crsr_xsize; int /*<<< orphan*/  crsr_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct amifb_par {TYPE_1__ crsr; } ;

/* Variables and functions */

__attribute__((used)) static int ami_get_fix_cursorinfo(struct fb_fix_cursorinfo *fix,
				  const struct amifb_par *par)
{
	fix->crsr_width = fix->crsr_xsize = par->crsr.width;
	fix->crsr_height = fix->crsr_ysize = par->crsr.height;
	fix->crsr_color1 = 17;
	fix->crsr_color2 = 18;
	return 0;
}