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
typedef  int /*<<< orphan*/  uint32_t ;
struct pipe_ctx {TYPE_3__* stream; } ;
typedef  enum vline_select { ____Placeholder_vline_select } vline_select ;
typedef  enum vertical_interrupt_ref_point { ____Placeholder_vertical_interrupt_ref_point } vertical_interrupt_ref_point ;
struct TYPE_5__ {int ref_point; } ;
struct TYPE_4__ {int ref_point; } ;
struct TYPE_6__ {TYPE_2__ periodic_interrupt1; TYPE_1__ periodic_interrupt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int INVALID_POINT ; 
#define  START_V_SYNC 129 
#define  START_V_UPDATE 128 
 int VLINE0 ; 
 int VLINE1 ; 
 int /*<<< orphan*/  calc_vupdate_position (struct pipe_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cal_vline_position(
		struct pipe_ctx *pipe_ctx,
		enum vline_select vline,
		uint32_t *start_line,
		uint32_t *end_line)
{
	enum vertical_interrupt_ref_point ref_point = INVALID_POINT;

	if (vline == VLINE0)
		ref_point = pipe_ctx->stream->periodic_interrupt0.ref_point;
	else if (vline == VLINE1)
		ref_point = pipe_ctx->stream->periodic_interrupt1.ref_point;

	switch (ref_point) {
	case START_V_UPDATE:
		calc_vupdate_position(
				pipe_ctx,
				start_line,
				end_line);
		break;
	case START_V_SYNC:
		// Suppose to do nothing because vsync is 0;
		break;
	default:
		ASSERT(0);
		break;
	}
}