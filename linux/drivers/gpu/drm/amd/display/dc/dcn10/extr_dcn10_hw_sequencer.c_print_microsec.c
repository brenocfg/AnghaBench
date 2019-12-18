#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int const uint32_t ;
struct dc_log_buffer_ctx {int dummy; } ;
struct dc_context {TYPE_3__* dc; } ;
struct TYPE_6__ {TYPE_2__* res_pool; } ;
struct TYPE_4__ {int dchub_ref_clock_inKhz; } ;
struct TYPE_5__ {TYPE_1__ ref_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTN_INFO (char*,unsigned int const,unsigned int const) ; 

void print_microsec(struct dc_context *dc_ctx,
	struct dc_log_buffer_ctx *log_ctx,
	uint32_t ref_cycle)
{
	const uint32_t ref_clk_mhz = dc_ctx->dc->res_pool->ref_clocks.dchub_ref_clock_inKhz / 1000;
	static const unsigned int frac = 1000;
	uint32_t us_x10 = (ref_cycle * frac) / ref_clk_mhz;

	DTN_INFO("  %11d.%03d",
			us_x10 / frac,
			us_x10 % frac);
}