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
struct dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_vga_and_power_gate_all_controllers (struct dc*) ; 
 int /*<<< orphan*/  power_down_all_hw_blocks (struct dc*) ; 

void dce110_power_down(struct dc *dc)
{
	power_down_all_hw_blocks(dc);
	disable_vga_and_power_gate_all_controllers(dc);
}