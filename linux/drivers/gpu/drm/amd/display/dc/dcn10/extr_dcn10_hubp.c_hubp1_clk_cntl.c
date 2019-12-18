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
typedef  int uint32_t ;
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUBP_CLK_CNTL ; 
 int /*<<< orphan*/  HUBP_CLOCK_ENABLE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

void hubp1_clk_cntl(struct hubp *hubp, bool enable)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uint32_t clk_enable = enable ? 1 : 0;

	REG_UPDATE(HUBP_CLK_CNTL, HUBP_CLOCK_ENABLE, clk_enable);
}