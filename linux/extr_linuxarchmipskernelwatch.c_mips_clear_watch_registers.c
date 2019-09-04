#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int watch_reg_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  write_c0_watchlo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_watchlo7 (int /*<<< orphan*/ ) ; 

void mips_clear_watch_registers(void)
{
	switch (current_cpu_data.watch_reg_count) {
	default:
		BUG();
	case 8:
		write_c0_watchlo7(0);
	case 7:
		write_c0_watchlo6(0);
	case 6:
		write_c0_watchlo5(0);
	case 5:
		write_c0_watchlo4(0);
	case 4:
		write_c0_watchlo3(0);
	case 3:
		write_c0_watchlo2(0);
	case 2:
		write_c0_watchlo1(0);
	case 1:
		write_c0_watchlo0(0);
	}
}