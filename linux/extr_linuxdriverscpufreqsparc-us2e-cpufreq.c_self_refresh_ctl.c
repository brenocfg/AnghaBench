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

/* Variables and functions */
 int /*<<< orphan*/  HBIRD_MEM_CNTL0_ADDR ; 
 unsigned long MCTRL0_SREFRESH_ENAB ; 
 unsigned long read_hbreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_hbreg (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void self_refresh_ctl(int enable)
{
	unsigned long mctrl = read_hbreg(HBIRD_MEM_CNTL0_ADDR);

	if (enable)
		mctrl |= MCTRL0_SREFRESH_ENAB;
	else
		mctrl &= ~MCTRL0_SREFRESH_ENAB;
	write_hbreg(HBIRD_MEM_CNTL0_ADDR, mctrl);
	(void) read_hbreg(HBIRD_MEM_CNTL0_ADDR);
}