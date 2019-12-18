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
 int /*<<< orphan*/  arcfb_lcd_update_vert (struct arcfb_par*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ceil64 (unsigned int) ; 
 unsigned int floor8 (unsigned int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcfb_lcd_update_horiz(struct arcfb_par *par, unsigned int left,
			unsigned int right, unsigned int top, unsigned int h)
{
	unsigned int distance, upper, lower;

	distance = h;
	upper = floor8(top);
	lower = min(upper + distance - 1, ceil64(upper));

	while (distance > 0) {
		distance -= ((lower - upper) + 1 );
		arcfb_lcd_update_vert(par, upper, lower, left, right);
		upper = lower + 1;
		lower = min(upper + distance - 1, ceil64(upper));
	}
}