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
struct gpmc_bool_timings {int /*<<< orphan*/  cycle2cyclediffcsen; int /*<<< orphan*/  cycle2cyclesamecsen; int /*<<< orphan*/  we_extra_delay; int /*<<< orphan*/  oe_extra_delay; int /*<<< orphan*/  adv_extra_delay; int /*<<< orphan*/  cs_extra_delay; int /*<<< orphan*/  time_para_granularity; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPMC_CONFIG1_TIME_PARA_GRAN ; 
 int /*<<< orphan*/  GPMC_CONFIG2_CSEXTRADELAY ; 
 int /*<<< orphan*/  GPMC_CONFIG3_ADVEXTRADELAY ; 
 int /*<<< orphan*/  GPMC_CONFIG4_OEEXTRADELAY ; 
 int /*<<< orphan*/  GPMC_CONFIG4_WEEXTRADELAY ; 
 int /*<<< orphan*/  GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN ; 
 int /*<<< orphan*/  GPMC_CONFIG6_CYCLE2CYCLESAMECSEN ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG1 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG2 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG3 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG4 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG6 ; 
 int /*<<< orphan*/  gpmc_cs_modify_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpmc_cs_bool_timings(int cs, const struct gpmc_bool_timings *p)
{
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG1,
			   GPMC_CONFIG1_TIME_PARA_GRAN,
			   p->time_para_granularity);
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG2,
			   GPMC_CONFIG2_CSEXTRADELAY, p->cs_extra_delay);
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG3,
			   GPMC_CONFIG3_ADVEXTRADELAY, p->adv_extra_delay);
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG4,
			   GPMC_CONFIG4_OEEXTRADELAY, p->oe_extra_delay);
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG4,
			   GPMC_CONFIG4_WEEXTRADELAY, p->we_extra_delay);
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG6,
			   GPMC_CONFIG6_CYCLE2CYCLESAMECSEN,
			   p->cycle2cyclesamecsen);
	gpmc_cs_modify_reg(cs, GPMC_CS_CONFIG6,
			   GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN,
			   p->cycle2cyclediffcsen);
}