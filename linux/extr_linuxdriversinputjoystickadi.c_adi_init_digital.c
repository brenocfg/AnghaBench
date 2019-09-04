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
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  mdelay (int const) ; 
 int /*<<< orphan*/  msleep (int const) ; 
 int /*<<< orphan*/  udelay (int const) ; 

__attribute__((used)) static void adi_init_digital(struct gameport *gameport)
{
	static const int seq[] = { 4, -2, -3, 10, -6, -11, -7, -9, 11, 0 };
	int i;

	for (i = 0; seq[i]; i++) {
		gameport_trigger(gameport);
		if (seq[i] > 0)
			msleep(seq[i]);
		if (seq[i] < 0) {
			mdelay(-seq[i]);
			udelay(-seq[i]*14);	/* It looks like mdelay() is off by approx 1.4% */
		}
	}
}