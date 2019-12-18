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
struct arcfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arcfb_lcd_update_page (struct arcfb_par*,unsigned int,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void arcfb_lcd_update_vert(struct arcfb_par *par, unsigned int top,
		unsigned int bottom, unsigned int left, unsigned int right)
{
	unsigned int distance, upper, lower;

	distance = (bottom - top) + 1;
	upper = top;
	lower = top + 7;

	while (distance > 0) {
		distance -= 8;
		arcfb_lcd_update_page(par, upper, left, right, 8);
		upper = lower + 1;
		lower = upper + 7;
	}
}