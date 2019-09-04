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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_DISPLAY_GAP_CNTL ; 
 int /*<<< orphan*/  DISPLAY_GAP_IGNORE ; 
 int /*<<< orphan*/  DISPLAY_GAP_VBLANK ; 
 int /*<<< orphan*/  DISP_GAP ; 
 int /*<<< orphan*/  DISP_GAP_MCHG ; 
 int /*<<< orphan*/  PHM_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixCG_DISPLAY_GAP_CNTL ; 

__attribute__((used)) static int smu7_enable_display_gap(struct pp_hwmgr *hwmgr)
{
	uint32_t display_gap =
			cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					ixCG_DISPLAY_GAP_CNTL);

	display_gap = PHM_SET_FIELD(display_gap, CG_DISPLAY_GAP_CNTL,
			DISP_GAP, DISPLAY_GAP_IGNORE);

	display_gap = PHM_SET_FIELD(display_gap, CG_DISPLAY_GAP_CNTL,
			DISP_GAP_MCHG, DISPLAY_GAP_VBLANK);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
			ixCG_DISPLAY_GAP_CNTL, display_gap);

	return 0;
}