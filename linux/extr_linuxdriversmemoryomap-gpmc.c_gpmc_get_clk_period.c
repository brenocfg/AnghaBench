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
typedef  enum gpmc_clk_domain { ____Placeholder_gpmc_clk_domain } gpmc_clk_domain ;

/* Variables and functions */
#define  GPMC_CD_CLK 129 
#define  GPMC_CD_FCLK 128 
 int /*<<< orphan*/  GPMC_CS_CONFIG1 ; 
 int gpmc_cs_read_reg (int,int /*<<< orphan*/ ) ; 
 unsigned long gpmc_get_fclk_period () ; 

__attribute__((used)) static unsigned long gpmc_get_clk_period(int cs, enum gpmc_clk_domain cd)
{

	unsigned long tick_ps = gpmc_get_fclk_period();
	u32 l;
	int div;

	switch (cd) {
	case GPMC_CD_CLK:
		/* get current clk divider */
		l = gpmc_cs_read_reg(cs, GPMC_CS_CONFIG1);
		div = (l & 0x03) + 1;
		/* get GPMC_CLK period */
		tick_ps *= div;
		break;
	case GPMC_CD_FCLK:
		/* FALL-THROUGH */
	default:
		break;
	}

	return tick_ps;

}