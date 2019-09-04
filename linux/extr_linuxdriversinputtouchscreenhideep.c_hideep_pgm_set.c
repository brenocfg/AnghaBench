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
struct hideep_ts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDEEP_FLASH_CACHE_CFG ; 
 int /*<<< orphan*/  HIDEEP_FLASH_TIM ; 
 int /*<<< orphan*/  HIDEEP_SYSCON_CLK_CON ; 
 int /*<<< orphan*/  HIDEEP_SYSCON_CLK_ENA ; 
 int /*<<< orphan*/  HIDEEP_SYSCON_PWR_CON ; 
 int /*<<< orphan*/  HIDEEP_SYSCON_SPC_CON ; 
 int /*<<< orphan*/  HIDEEP_SYSCON_WDT_CON ; 
 int /*<<< orphan*/  hideep_pgm_w_reg (struct hideep_ts*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hideep_pgm_set(struct hideep_ts *ts)
{
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_WDT_CON, 0x00);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_SPC_CON, 0x00);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_CLK_ENA, 0xFF);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_CLK_CON, 0x01);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_PWR_CON, 0x01);
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_TIM, 0x03);
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CACHE_CFG, 0x00);
}