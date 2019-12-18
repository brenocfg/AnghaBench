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
struct dc_sink_init_data {struct dc_link* link; int /*<<< orphan*/  converter_disable_audio; int /*<<< orphan*/  dongle_max_pix_clk; int /*<<< orphan*/  sink_signal; } ;
struct dc_sink {int /*<<< orphan*/  sink_id; int /*<<< orphan*/ * dc_container_id; int /*<<< orphan*/  converter_disable_audio; int /*<<< orphan*/  dongle_max_pix_clk; TYPE_1__* ctx; struct dc_link* link; int /*<<< orphan*/  sink_signal; } ;
struct dc_link {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dc_sink_id_count; } ;

/* Variables and functions */

__attribute__((used)) static bool construct(struct dc_sink *sink, const struct dc_sink_init_data *init_params)
{

	struct dc_link *link = init_params->link;

	if (!link)
		return false;

	sink->sink_signal = init_params->sink_signal;
	sink->link = link;
	sink->ctx = link->ctx;
	sink->dongle_max_pix_clk = init_params->dongle_max_pix_clk;
	sink->converter_disable_audio = init_params->converter_disable_audio;
	sink->dc_container_id = NULL;
	sink->sink_id = init_params->link->ctx->dc_sink_id_count;
	// increment dc_sink_id_count because we don't want two sinks with same ID
	// unless they are actually the same
	init_params->link->ctx->dc_sink_id_count++;

	return true;
}