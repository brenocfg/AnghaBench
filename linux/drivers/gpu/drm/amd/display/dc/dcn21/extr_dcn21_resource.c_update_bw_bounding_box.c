#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pipe_count; TYPE_1__* res_cap; } ;
struct dcn21_resource_pool {TYPE_2__ base; } ;
struct dc {int /*<<< orphan*/  res_pool; } ;
struct clk_limit_table {int num_entries; TYPE_4__* entries; } ;
struct clk_bw_params {int /*<<< orphan*/  num_channels; struct clk_limit_table clk_table; } ;
struct TYPE_12__ {int /*<<< orphan*/  max_num_dpp; int /*<<< orphan*/  max_num_otg; } ;
struct TYPE_11__ {scalar_t__ num_states; TYPE_3__* clock_limits; int /*<<< orphan*/  num_chans; } ;
struct TYPE_10__ {int memclk_mhz; int /*<<< orphan*/  socclk_mhz; int /*<<< orphan*/  fclk_mhz; int /*<<< orphan*/  dcfclk_mhz; } ;
struct TYPE_9__ {int state; int dram_speed_mts; int /*<<< orphan*/  socclk_mhz; int /*<<< orphan*/  fabricclk_mhz; int /*<<< orphan*/  dcfclk_mhz; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_timing_generator; } ;

/* Variables and functions */
 struct dcn21_resource_pool* TO_DCN21_RES_POOL (int /*<<< orphan*/ ) ; 
 TYPE_6__ dcn2_1_ip ; 
 TYPE_5__ dcn2_1_soc ; 

__attribute__((used)) static void update_bw_bounding_box(struct dc *dc, struct clk_bw_params *bw_params)
{
	struct dcn21_resource_pool *pool = TO_DCN21_RES_POOL(dc->res_pool);
	struct clk_limit_table *clk_table = &bw_params->clk_table;
	int i;

	dcn2_1_ip.max_num_otg = pool->base.res_cap->num_timing_generator;
	dcn2_1_ip.max_num_dpp = pool->base.pipe_count;
	dcn2_1_soc.num_chans = bw_params->num_channels;
	dcn2_1_soc.num_states = 0;

	for (i = 0; i < clk_table->num_entries; i++) {

		dcn2_1_soc.clock_limits[i].state = i;
		dcn2_1_soc.clock_limits[i].dcfclk_mhz = clk_table->entries[i].dcfclk_mhz;
		dcn2_1_soc.clock_limits[i].fabricclk_mhz = clk_table->entries[i].fclk_mhz;
		dcn2_1_soc.clock_limits[i].socclk_mhz = clk_table->entries[i].socclk_mhz;
		/* This is probably wrong, TODO: find correct calculation */
		dcn2_1_soc.clock_limits[i].dram_speed_mts = clk_table->entries[i].memclk_mhz * 16 / 1000;
		dcn2_1_soc.num_states++;
	}
}