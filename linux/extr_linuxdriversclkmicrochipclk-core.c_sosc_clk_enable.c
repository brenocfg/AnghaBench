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
struct pic32_sec_osc {int status_mask; int /*<<< orphan*/  status_reg; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  enable_mask; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_SET (int /*<<< orphan*/ ) ; 
 struct pic32_sec_osc* clkhw_to_sosc (struct clk_hw*) ; 
 int /*<<< orphan*/  pic32_syskey_unlock () ; 
 int readl_poll_timeout_atomic (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sosc_clk_enable(struct clk_hw *hw)
{
	struct pic32_sec_osc *sosc = clkhw_to_sosc(hw);
	u32 v;

	/* enable SOSC */
	pic32_syskey_unlock();
	writel(sosc->enable_mask, PIC32_SET(sosc->enable_reg));

	/* wait till warm-up period expires or ready-status is updated */
	return readl_poll_timeout_atomic(sosc->status_reg, v,
					 v & sosc->status_mask, 1, 100);
}