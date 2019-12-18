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
struct _vcs_dpi_display_dlg_regs_st {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_DEDCN21_142_wa_for_hostvm_deadline (struct hubp*,struct _vcs_dpi_display_dlg_regs_st*) ; 
 int /*<<< orphan*/  hubp2_program_deadline (struct hubp*,struct _vcs_dpi_display_dlg_regs_st*,struct _vcs_dpi_display_ttu_regs_st*) ; 

void hubp21_program_deadline(
		struct hubp *hubp,
		struct _vcs_dpi_display_dlg_regs_st *dlg_attr,
		struct _vcs_dpi_display_ttu_regs_st *ttu_attr)
{
	hubp2_program_deadline(hubp, dlg_attr, ttu_attr);

	apply_DEDCN21_142_wa_for_hostvm_deadline(hubp, dlg_attr);
}