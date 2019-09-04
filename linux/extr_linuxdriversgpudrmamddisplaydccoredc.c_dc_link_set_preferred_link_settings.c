#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dc_stream_state {int dummy; } ;
struct dc_link_settings {scalar_t__ lane_count; scalar_t__ link_rate; } ;
struct dc_link {struct dc_link_settings preferred_link_setting; TYPE_4__* dc; } ;
struct dc {int dummy; } ;
struct TYPE_8__ {TYPE_3__* current_state; } ;
struct TYPE_6__ {TYPE_1__* pipe_ctx; } ;
struct TYPE_7__ {TYPE_2__ res_ctx; } ;
struct TYPE_5__ {struct dc_stream_state* stream; } ;

/* Variables and functions */
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  decide_link_settings (struct dc_stream_state*,struct dc_link_settings*) ; 
 int /*<<< orphan*/  dp_retrain_link_dp_test (struct dc_link*,struct dc_link_settings*,int) ; 

void dc_link_set_preferred_link_settings(struct dc *dc,
					 struct dc_link_settings *link_setting,
					 struct dc_link *link)
{
	struct dc_link_settings store_settings = *link_setting;
	struct dc_stream_state *link_stream =
		link->dc->current_state->res_ctx.pipe_ctx[0].stream;

	link->preferred_link_setting = store_settings;
	if (link_stream)
		decide_link_settings(link_stream, &store_settings);

	if ((store_settings.lane_count != LANE_COUNT_UNKNOWN) &&
		(store_settings.link_rate != LINK_RATE_UNKNOWN))
		dp_retrain_link_dp_test(link, &store_settings, false);
}