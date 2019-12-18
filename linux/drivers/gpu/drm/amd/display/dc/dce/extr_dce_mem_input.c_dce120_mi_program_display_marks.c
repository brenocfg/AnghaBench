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
typedef  int uint32_t ;
struct mem_input {TYPE_3__* ctx; } ;
struct dce_watermarks {int /*<<< orphan*/  d_mark; int /*<<< orphan*/  c_mark; int /*<<< orphan*/  b_mark; int /*<<< orphan*/  a_mark; } ;
struct dce_mem_input {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct TYPE_4__ {scalar_t__ disable_stutter; } ;
struct TYPE_5__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPG_PIPE_STUTTER_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STUTTER_ENABLE ; 
 int /*<<< orphan*/  STUTTER_IGNORE_FBC ; 
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 
 int /*<<< orphan*/  dce120_program_stutter_watermark (struct dce_mem_input*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce120_program_urgency_watermark (struct dce_mem_input*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  program_nbp_watermark (struct dce_mem_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce120_mi_program_display_marks(struct mem_input *mi,
	struct dce_watermarks nbp,
	struct dce_watermarks stutter_exit,
	struct dce_watermarks stutter_entry,
	struct dce_watermarks urgent,
	uint32_t total_dest_line_time_ns)
{
	struct dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	uint32_t stutter_en = mi->ctx->dc->debug.disable_stutter ? 0 : 1;

	dce120_program_urgency_watermark(dce_mi, 0, /* set a */
			urgent.a_mark, total_dest_line_time_ns);
	dce120_program_urgency_watermark(dce_mi, 1, /* set b */
			urgent.b_mark, total_dest_line_time_ns);
	dce120_program_urgency_watermark(dce_mi, 2, /* set c */
			urgent.c_mark, total_dest_line_time_ns);
	dce120_program_urgency_watermark(dce_mi, 3, /* set d */
			urgent.d_mark, total_dest_line_time_ns);

	REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_ENABLE, stutter_en,
		STUTTER_IGNORE_FBC, 1);
	program_nbp_watermark(dce_mi, 0, nbp.a_mark); /* set a */
	program_nbp_watermark(dce_mi, 1, nbp.b_mark); /* set b */
	program_nbp_watermark(dce_mi, 2, nbp.c_mark); /* set c */
	program_nbp_watermark(dce_mi, 3, nbp.d_mark); /* set d */

	dce120_program_stutter_watermark(dce_mi, 0, stutter_exit.a_mark, stutter_entry.a_mark); /* set a */
	dce120_program_stutter_watermark(dce_mi, 1, stutter_exit.b_mark, stutter_entry.b_mark); /* set b */
	dce120_program_stutter_watermark(dce_mi, 2, stutter_exit.c_mark, stutter_entry.c_mark); /* set c */
	dce120_program_stutter_watermark(dce_mi, 3, stutter_exit.d_mark, stutter_entry.d_mark); /* set d */
}