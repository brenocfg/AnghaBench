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
struct gpmc_timings {int cs_on; int cs_rd_off; int cs_wr_off; int adv_on; int adv_rd_off; int adv_wr_off; int we_on; int we_off; int oe_on; int oe_off; int page_burst_access; int access; int rd_cycle; int wr_cycle; int bus_turnaround; int cycle2cycle_delay; int wait_monitoring; int clk_activation; int wr_access; int wr_data_mux_bus; } ;

/* Variables and functions */

__attribute__((used)) static void gpmc_convert_ps_to_ns(struct gpmc_timings *t)
{
	t->cs_on /= 1000;
	t->cs_rd_off /= 1000;
	t->cs_wr_off /= 1000;
	t->adv_on /= 1000;
	t->adv_rd_off /= 1000;
	t->adv_wr_off /= 1000;
	t->we_on /= 1000;
	t->we_off /= 1000;
	t->oe_on /= 1000;
	t->oe_off /= 1000;
	t->page_burst_access /= 1000;
	t->access /= 1000;
	t->rd_cycle /= 1000;
	t->wr_cycle /= 1000;
	t->bus_turnaround /= 1000;
	t->cycle2cycle_delay /= 1000;
	t->wait_monitoring /= 1000;
	t->clk_activation /= 1000;
	t->wr_access /= 1000;
	t->wr_data_mux_bus /= 1000;
}