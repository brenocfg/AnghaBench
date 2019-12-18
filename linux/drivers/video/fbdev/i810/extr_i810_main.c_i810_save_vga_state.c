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
struct i810fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i810_save_2d (struct i810fb_par*) ; 
 int /*<<< orphan*/  i810_save_vga (struct i810fb_par*) ; 
 int /*<<< orphan*/  i810_save_vgax (struct i810fb_par*) ; 

__attribute__((used)) static void i810_save_vga_state(struct i810fb_par *par)
{
	i810_save_vga(par);
	i810_save_vgax(par);
	i810_save_2d(par);
}