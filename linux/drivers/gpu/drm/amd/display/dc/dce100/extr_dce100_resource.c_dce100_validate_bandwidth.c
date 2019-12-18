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
struct TYPE_10__ {int dispclk_khz; int yclk_khz; } ;
struct TYPE_11__ {TYPE_4__ dce; } ;
struct TYPE_12__ {TYPE_5__ bw; } ;
struct TYPE_9__ {TYPE_2__* pipe_ctx; } ;
struct dc_state {TYPE_6__ bw_ctx; TYPE_3__ res_ctx; } ;
struct dc {TYPE_1__* res_pool; } ;
struct TYPE_8__ {scalar_t__ stream; } ;
struct TYPE_7__ {int pipe_count; } ;

/* Variables and functions */
 int MEMORY_TYPE_MULTIPLIER_CZ ; 

bool dce100_validate_bandwidth(
	struct dc  *dc,
	struct dc_state *context,
	bool fast_validate)
{
	int i;
	bool at_least_one_pipe = false;

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		if (context->res_ctx.pipe_ctx[i].stream)
			at_least_one_pipe = true;
	}

	if (at_least_one_pipe) {
		/* TODO implement when needed but for now hardcode max value*/
		context->bw_ctx.bw.dce.dispclk_khz = 681000;
		context->bw_ctx.bw.dce.yclk_khz = 250000 * MEMORY_TYPE_MULTIPLIER_CZ;
	} else {
		context->bw_ctx.bw.dce.dispclk_khz = 0;
		context->bw_ctx.bw.dce.yclk_khz = 0;
	}

	return true;
}