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
struct w100fb_par {int xres; int yres; } ;

/* Variables and functions */
 int BITS_PER_PIXEL ; 
 scalar_t__ MEM_WINDOW_BASE ; 
 scalar_t__ W100_FB_BASE ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ remapped_fbuf ; 

__attribute__((used)) static void w100fb_clear_screen(struct w100fb_par *par)
{
	memset_io(remapped_fbuf + (W100_FB_BASE-MEM_WINDOW_BASE), 0, (par->xres * par->yres * BITS_PER_PIXEL/8));
}