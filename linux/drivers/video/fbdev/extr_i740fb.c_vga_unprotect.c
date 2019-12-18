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
struct i740fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_ATT_W ; 
 int /*<<< orphan*/  VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 int /*<<< orphan*/  i740inb (struct i740fb_par*,int) ; 
 int /*<<< orphan*/  i740outb (struct i740fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i740outreg_mask (struct i740fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vga_unprotect(struct i740fb_par *par)
{
	/* reenable display */
	i740outreg_mask(par, VGA_SEQ_I, VGA_SEQ_CLOCK_MODE, 0, 0x20);

	i740inb(par, 0x3DA);
	i740outb(par, VGA_ATT_W, 0x20);	/* disable palette access */
}