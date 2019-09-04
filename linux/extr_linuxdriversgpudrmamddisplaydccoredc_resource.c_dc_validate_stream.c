#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timing_generator {TYPE_2__* funcs; } ;
struct dc_stream_state {int /*<<< orphan*/  timing; TYPE_4__* sink; } ;
struct dc_link {TYPE_5__* link_enc; } ;
struct dc {TYPE_1__* res_pool; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {struct dc_link* link; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* validate_output_with_stream ) (TYPE_5__*,struct dc_stream_state*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* validate_timing ) (struct timing_generator*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {struct timing_generator** timing_generators; } ;

/* Variables and functions */
 int DC_FAIL_CONTROLLER_VALIDATE ; 
 int DC_FAIL_ENC_VALIDATE ; 
 int DC_OK ; 
 int /*<<< orphan*/  calculate_phy_pix_clks (struct dc_stream_state*) ; 
 int dc_link_validate_mode_timing (struct dc_stream_state*,struct dc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,struct dc_stream_state*) ; 

enum dc_status dc_validate_stream(struct dc *dc, struct dc_stream_state *stream)
{
	struct dc  *core_dc = dc;
	struct dc_link *link = stream->sink->link;
	struct timing_generator *tg = core_dc->res_pool->timing_generators[0];
	enum dc_status res = DC_OK;

	calculate_phy_pix_clks(stream);

	if (!tg->funcs->validate_timing(tg, &stream->timing))
		res = DC_FAIL_CONTROLLER_VALIDATE;

	if (res == DC_OK)
		if (!link->link_enc->funcs->validate_output_with_stream(
						link->link_enc, stream))
			res = DC_FAIL_ENC_VALIDATE;

	/* TODO: validate audio ASIC caps, encoder */

	if (res == DC_OK)
		res = dc_link_validate_mode_timing(stream,
		      link,
		      &stream->timing);

	return res;
}