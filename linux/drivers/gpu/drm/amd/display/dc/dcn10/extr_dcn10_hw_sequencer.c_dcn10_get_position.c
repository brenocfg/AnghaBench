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
struct TYPE_5__ {TYPE_3__* tg; } ;
struct pipe_ctx {TYPE_2__ stream_res; } ;
struct crtc_position {int dummy; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_position ) (TYPE_3__*,struct crtc_position*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct crtc_position*) ; 

__attribute__((used)) static void dcn10_get_position(struct pipe_ctx **pipe_ctx,
		int num_pipes,
		struct crtc_position *position)
{
	int i = 0;

	/* TODO: handle pipes > 1
	 */
	for (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->get_position(pipe_ctx[i]->stream_res.tg, position);
}