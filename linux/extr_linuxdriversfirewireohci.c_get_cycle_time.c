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
typedef  int u32 ;
struct fw_ohci {int quirks; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 int QUIRK_CYCLE_TIMER ; 
 int cycle_timer_ticks (int) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_cycle_time(struct fw_ohci *ohci)
{
	u32 c0, c1, c2;
	u32 t0, t1, t2;
	s32 diff01, diff12;
	int i;

	c2 = reg_read(ohci, OHCI1394_IsochronousCycleTimer);

	if (ohci->quirks & QUIRK_CYCLE_TIMER) {
		i = 0;
		c1 = c2;
		c2 = reg_read(ohci, OHCI1394_IsochronousCycleTimer);
		do {
			c0 = c1;
			c1 = c2;
			c2 = reg_read(ohci, OHCI1394_IsochronousCycleTimer);
			t0 = cycle_timer_ticks(c0);
			t1 = cycle_timer_ticks(c1);
			t2 = cycle_timer_ticks(c2);
			diff01 = t1 - t0;
			diff12 = t2 - t1;
		} while ((diff01 <= 0 || diff12 <= 0 ||
			  diff01 / diff12 >= 2 || diff12 / diff01 >= 2)
			 && i++ < 20);
	}

	return c2;
}