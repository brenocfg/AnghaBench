#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* tg; } ;
struct pipe_ctx {TYPE_2__ stream_res; } ;
struct dc_context {int dummy; } ;
struct dc {struct dc_context* ctx; } ;
struct TYPE_8__ {TYPE_1__* funcs; int /*<<< orphan*/  inst; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable_reset_trigger ) (TYPE_3__*) ;int /*<<< orphan*/  (* enable_reset_trigger ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_SYNC_INFO (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  wait_for_reset_trigger_to_occur (struct dc_context*,TYPE_3__*) ; 

__attribute__((used)) static void dcn10_enable_timing_synchronization(
	struct dc *dc,
	int group_index,
	int group_size,
	struct pipe_ctx *grouped_pipes[])
{
	struct dc_context *dc_ctx = dc->ctx;
	int i;

	DC_SYNC_INFO("Setting up OTG reset trigger\n");

	for (i = 1; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->enable_reset_trigger(
				grouped_pipes[i]->stream_res.tg,
				grouped_pipes[0]->stream_res.tg->inst);

	DC_SYNC_INFO("Waiting for trigger\n");

	/* Need to get only check 1 pipe for having reset as all the others are
	 * synchronized. Look at last pipe programmed to reset.
	 */

	wait_for_reset_trigger_to_occur(dc_ctx, grouped_pipes[1]->stream_res.tg);
	for (i = 1; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->disable_reset_trigger(
				grouped_pipes[i]->stream_res.tg);

	DC_SYNC_INFO("Sync complete\n");
}