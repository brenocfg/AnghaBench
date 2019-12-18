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
 int /*<<< orphan*/  DPG_PIPE_STUTTER_CONTROL ; 
 int /*<<< orphan*/  DPG_PIPE_STUTTER_CONTROL2 ; 
 int /*<<< orphan*/  DPG_WATERMARK_MASK_CONTROL ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STUTTER_EXIT_SELF_REFRESH_WATERMARK ; 
 int /*<<< orphan*/  STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK ; 

__attribute__((used)) static void program_stutter_watermark(
	struct dce_mem_input *dce_mi,
	uint32_t wm_select,
	uint32_t stutter_mark)
{
	REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK, wm_select);

	if (REG(DPG_PIPE_STUTTER_CONTROL2))
		REG_UPDATE(DPG_PIPE_STUTTER_CONTROL2,
				STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark);
	else
		REG_UPDATE(DPG_PIPE_STUTTER_CONTROL,
				STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark);
}