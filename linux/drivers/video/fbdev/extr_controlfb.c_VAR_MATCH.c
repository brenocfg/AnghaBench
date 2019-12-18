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
struct fb_var_screeninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIRTY_CMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bits_per_pixel ; 
 int /*<<< orphan*/  blue ; 
 int /*<<< orphan*/  green ; 
 int /*<<< orphan*/  red ; 
 int /*<<< orphan*/  xres ; 
 int /*<<< orphan*/  xres_virtual ; 
 int /*<<< orphan*/  yres ; 
 int /*<<< orphan*/  yres_virtual ; 

__attribute__((used)) static inline int VAR_MATCH(struct fb_var_screeninfo *x, struct fb_var_screeninfo *y)
{
	return (!DIRTY(bits_per_pixel) && !DIRTY(xres)
		&& !DIRTY(yres) && !DIRTY(xres_virtual)
		&& !DIRTY(yres_virtual)
		&& !DIRTY_CMAP(red) && !DIRTY_CMAP(green) && !DIRTY_CMAP(blue));
}