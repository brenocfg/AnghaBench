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
struct TYPE_2__ {int /*<<< orphan*/  fck; int /*<<< orphan*/  bus_pick_width; int /*<<< orphan*/  bus_pick_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOSSI_INIT1_REG ; 
 int /*<<< orphan*/  WR_ACCESS ; 
 int /*<<< orphan*/  _set_bits_per_cycle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_data (void const*,unsigned int) ; 
 int /*<<< orphan*/  set_cycles (unsigned int) ; 
 int /*<<< orphan*/  set_timing (int /*<<< orphan*/ ) ; 
 TYPE_1__ sossi ; 
 int /*<<< orphan*/  sossi_clear_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sossi_start_transfer () ; 
 int /*<<< orphan*/  sossi_stop_transfer () ; 
 int /*<<< orphan*/  wait_end_of_write () ; 

__attribute__((used)) static void sossi_write_command(const void *data, unsigned int len)
{
	clk_enable(sossi.fck);
	set_timing(WR_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_clear_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(len);
	sossi_start_transfer();
	send_data(data, len);
	sossi_stop_transfer();
	wait_end_of_write();
	clk_disable(sossi.fck);
}