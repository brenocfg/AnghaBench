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
typedef  int u16 ;
struct aty128fb_par {int fifo_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_STAT ; 
 int /*<<< orphan*/  aty128_reset_engine (struct aty128fb_par*) ; 
 int aty_ld_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_wait_for_fifo(u16 entries, struct aty128fb_par *par)
{
	int i;

	for (;;) {
		for (i = 0; i < 2000000; i++) {
			par->fifo_slots = aty_ld_le32(GUI_STAT) & 0x0fff;
			if (par->fifo_slots >= entries)
				return;
		}
		aty128_reset_engine(par);
	}
}