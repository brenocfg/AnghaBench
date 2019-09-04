#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dc_state {int /*<<< orphan*/  dis_clk; } ;
struct dc {TYPE_1__* res_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccg; } ;

/* Variables and functions */

void dc_resource_state_construct(
		const struct dc *dc,
		struct dc_state *dst_ctx)
{
	dst_ctx->dis_clk = dc->res_pool->dccg;
}