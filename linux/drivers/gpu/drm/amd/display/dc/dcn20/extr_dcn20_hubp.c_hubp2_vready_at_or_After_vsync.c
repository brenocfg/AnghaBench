#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
struct _vcs_dpi_display_pipe_dest_params_st {scalar_t__ vstartup_start; scalar_t__ vready_offset; scalar_t__ vupdate_width; scalar_t__ vupdate_offset; scalar_t__ htotal; scalar_t__ vblank_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBP_CNTL ; 
 int /*<<< orphan*/  HUBPREQ_DEBUG_DB ; 
 int /*<<< orphan*/  HUBP_VREADY_AT_OR_AFTER_VSYNC ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 

void hubp2_vready_at_or_After_vsync(struct hubp *hubp,
		struct _vcs_dpi_display_pipe_dest_params_st *pipe_dest)
{
	uint32_t value = 0;
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	/* disable_dlg_test_mode Set 9th bit to 1 to disable "dv" mode */
	REG_WRITE(HUBPREQ_DEBUG_DB, 1 << 8);
	/*
	if (VSTARTUP_START - (VREADY_OFFSET+VUPDATE_WIDTH+VUPDATE_OFFSET)/htotal)
	<= OTG_V_BLANK_END
		Set HUBP_VREADY_AT_OR_AFTER_VSYNC = 1
	else
		Set HUBP_VREADY_AT_OR_AFTER_VSYNC = 0
	*/
	if ((pipe_dest->vstartup_start - (pipe_dest->vready_offset+pipe_dest->vupdate_width
		+ pipe_dest->vupdate_offset) / pipe_dest->htotal) <= pipe_dest->vblank_end) {
		value = 1;
	} else
		value = 0;
	REG_UPDATE(DCHUBP_CNTL, HUBP_VREADY_AT_OR_AFTER_VSYNC, value);
}