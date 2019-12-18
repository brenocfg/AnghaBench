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
struct hubp {int dummy; } ;
struct _vcs_dpi_display_ttu_regs_st {int dummy; } ;
struct _vcs_dpi_display_rq_regs_st {int dummy; } ;
struct _vcs_dpi_display_pipe_dest_params_st {int dummy; } ;
struct _vcs_dpi_display_dlg_regs_st {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hubp21_program_deadline (struct hubp*,struct _vcs_dpi_display_dlg_regs_st*,struct _vcs_dpi_display_ttu_regs_st*) ; 
 int /*<<< orphan*/  hubp21_program_requestor (struct hubp*,struct _vcs_dpi_display_rq_regs_st*) ; 
 int /*<<< orphan*/  hubp2_vready_at_or_After_vsync (struct hubp*,struct _vcs_dpi_display_pipe_dest_params_st*) ; 

__attribute__((used)) static void hubp21_setup(
		struct hubp *hubp,
		struct _vcs_dpi_display_dlg_regs_st *dlg_attr,
		struct _vcs_dpi_display_ttu_regs_st *ttu_attr,
		struct _vcs_dpi_display_rq_regs_st *rq_regs,
		struct _vcs_dpi_display_pipe_dest_params_st *pipe_dest)
{
	/* otg is locked when this func is called. Register are double buffered.
	 * disable the requestors is not needed
	 */

	hubp2_vready_at_or_After_vsync(hubp, pipe_dest);
	hubp21_program_requestor(hubp, rq_regs);
	hubp21_program_deadline(hubp, dlg_attr, ttu_attr);

}