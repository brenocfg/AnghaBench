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
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_5__* tg; } ;
struct pipe_ctx {TYPE_4__ stream_res; } ;
struct TYPE_8__ {scalar_t__ blnd_crtc_trigger; } ;
struct dce_hwseq {TYPE_3__ wa; TYPE_2__* masks; } ;
struct dc {struct dce_hwseq* hwseq; } ;
struct TYPE_10__ {size_t inst; TYPE_1__* funcs; } ;
struct TYPE_7__ {scalar_t__ BLND_BLND_V_UPDATE_LOCK; } ;
struct TYPE_6__ {scalar_t__ (* is_blanked ) (TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLND_BLND_V_UPDATE_LOCK ; 
 int /*<<< orphan*/  BLND_DCP_GRPH_V_UPDATE_LOCK ; 
 int /*<<< orphan*/  BLND_SCL_V_UPDATE_LOCK ; 
 int /*<<< orphan*/ * BLND_V_UPDATE_LOCK ; 
 int /*<<< orphan*/  BLND_V_UPDATE_LOCK_MODE ; 
 int /*<<< orphan*/ * CRTC_H_BLANK_START_END ; 
 int REG_GET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_5__*) ; 

void dce_pipe_control_lock(struct dc *dc,
		struct pipe_ctx *pipe,
		bool lock)
{
	uint32_t lock_val = lock ? 1 : 0;
	uint32_t dcp_grph, scl, blnd, update_lock_mode, val;
	struct dce_hwseq *hws = dc->hwseq;

	/* Not lock pipe when blank */
	if (lock && pipe->stream_res.tg->funcs->is_blanked &&
	    pipe->stream_res.tg->funcs->is_blanked(pipe->stream_res.tg))
		return;

	val = REG_GET_4(BLND_V_UPDATE_LOCK[pipe->stream_res.tg->inst],
			BLND_DCP_GRPH_V_UPDATE_LOCK, &dcp_grph,
			BLND_SCL_V_UPDATE_LOCK, &scl,
			BLND_BLND_V_UPDATE_LOCK, &blnd,
			BLND_V_UPDATE_LOCK_MODE, &update_lock_mode);

	dcp_grph = lock_val;
	scl = lock_val;
	blnd = lock_val;
	update_lock_mode = lock_val;

	REG_SET_2(BLND_V_UPDATE_LOCK[pipe->stream_res.tg->inst], val,
			BLND_DCP_GRPH_V_UPDATE_LOCK, dcp_grph,
			BLND_SCL_V_UPDATE_LOCK, scl);

	if (hws->masks->BLND_BLND_V_UPDATE_LOCK != 0)
		REG_SET_2(BLND_V_UPDATE_LOCK[pipe->stream_res.tg->inst], val,
				BLND_BLND_V_UPDATE_LOCK, blnd,
				BLND_V_UPDATE_LOCK_MODE, update_lock_mode);

	if (hws->wa.blnd_crtc_trigger) {
		if (!lock) {
			uint32_t value = REG_READ(CRTC_H_BLANK_START_END[pipe->stream_res.tg->inst]);
			REG_WRITE(CRTC_H_BLANK_START_END[pipe->stream_res.tg->inst], value);
		}
	}
}