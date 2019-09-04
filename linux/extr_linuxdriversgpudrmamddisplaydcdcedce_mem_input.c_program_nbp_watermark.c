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
struct dce_mem_input {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPG_PIPE_LOW_POWER_CONTROL ; 
 int /*<<< orphan*/  DPG_PIPE_NB_PSTATE_CHANGE_CONTROL ; 
 int /*<<< orphan*/  DPG_WATERMARK_MASK_CONTROL ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_ENABLE ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_URGENT_DURING_REQUEST ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_WATERMARK ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_WATERMARK_MASK ; 
 int /*<<< orphan*/  PSTATE_CHANGE_ENABLE ; 
 int /*<<< orphan*/  PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST ; 
 int /*<<< orphan*/  PSTATE_CHANGE_URGENT_DURING_REQUEST ; 
 int /*<<< orphan*/  PSTATE_CHANGE_WATERMARK ; 
 int /*<<< orphan*/  PSTATE_CHANGE_WATERMARK_MASK ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void program_nbp_watermark(
	struct dce_mem_input *dce_mi,
	uint32_t wm_select,
	uint32_t nbp_wm)
{
	if (REG(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL)) {
		REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
				NB_PSTATE_CHANGE_WATERMARK_MASK, wm_select);

		REG_UPDATE_3(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
				NB_PSTATE_CHANGE_ENABLE, 1,
				NB_PSTATE_CHANGE_URGENT_DURING_REQUEST, 1,
				NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, 1);

		REG_UPDATE(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
				NB_PSTATE_CHANGE_WATERMARK, nbp_wm);
	}

	if (REG(DPG_PIPE_LOW_POWER_CONTROL)) {
		REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
				PSTATE_CHANGE_WATERMARK_MASK, wm_select);

		REG_UPDATE_3(DPG_PIPE_LOW_POWER_CONTROL,
				PSTATE_CHANGE_ENABLE, 1,
				PSTATE_CHANGE_URGENT_DURING_REQUEST, 1,
				PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, 1);

		REG_UPDATE(DPG_PIPE_LOW_POWER_CONTROL,
				PSTATE_CHANGE_WATERMARK, nbp_wm);
	}
}