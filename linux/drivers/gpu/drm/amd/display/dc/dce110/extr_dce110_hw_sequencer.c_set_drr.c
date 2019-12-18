#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* tg; } ;
struct pipe_ctx {TYPE_2__ stream_res; } ;
struct drr_params {unsigned int vertical_total_max; unsigned int vertical_total_min; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_static_screen_control ) (TYPE_3__*,unsigned int) ;int /*<<< orphan*/  (* set_drr ) (TYPE_3__*,struct drr_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct drr_params*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static void set_drr(struct pipe_ctx **pipe_ctx,
		int num_pipes, unsigned int vmin, unsigned int vmax,
		unsigned int vmid, unsigned int vmid_frame_number)
{
	int i = 0;
	struct drr_params params = {0};
	// DRR should set trigger event to monitor surface update event
	unsigned int event_triggers = 0x80;

	params.vertical_total_max = vmax;
	params.vertical_total_min = vmin;

	/* TODO: If multiple pipes are to be supported, you need
	 * some GSL stuff. Static screen triggers may be programmed differently
	 * as well.
	 */
	for (i = 0; i < num_pipes; i++) {
		pipe_ctx[i]->stream_res.tg->funcs->set_drr(
			pipe_ctx[i]->stream_res.tg, &params);

		if (vmax != 0 && vmin != 0)
			pipe_ctx[i]->stream_res.tg->funcs->set_static_screen_control(
					pipe_ctx[i]->stream_res.tg,
					event_triggers);
	}
}