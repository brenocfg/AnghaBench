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
struct clk_states {int /*<<< orphan*/  dprefclk_khz; } ;
struct clk_state_registers_and_bypass {int /*<<< orphan*/  dprefclk; int /*<<< orphan*/  member_0; } ;
struct clk_mgr {int dummy; } ;
struct clk_log_info {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  rn_dump_clk_registers (struct clk_state_registers_and_bypass*,struct clk_mgr*,struct clk_log_info*) ; 

void rn_get_clk_states(struct clk_mgr *clk_mgr_base, struct clk_states *s)
{
	struct clk_state_registers_and_bypass sb = { 0 };
	struct clk_log_info log_info = { 0 };

	rn_dump_clk_registers(&sb, clk_mgr_base, &log_info);

	s->dprefclk_khz = sb.dprefclk;
}