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
struct mem_input {int /*<<< orphan*/  ctx; } ;
struct dce_watermarks {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  program_nbp_watermark_l (int /*<<< orphan*/ ,struct dce_watermarks) ; 
 int /*<<< orphan*/  program_stutter_watermark_l (int /*<<< orphan*/ ,struct dce_watermarks) ; 
 int /*<<< orphan*/  program_urgency_watermark_l (int /*<<< orphan*/ ,struct dce_watermarks,int /*<<< orphan*/ ) ; 

void dce_mem_input_v_program_display_marks(
	struct mem_input *mem_input,
	struct dce_watermarks nbp,
	struct dce_watermarks stutter,
	struct dce_watermarks stutter_enter,
	struct dce_watermarks urgent,
	uint32_t total_dest_line_time_ns)
{
	program_urgency_watermark_l(
		mem_input->ctx,
		urgent,
		total_dest_line_time_ns);

	program_nbp_watermark_l(
		mem_input->ctx,
		nbp);

	program_stutter_watermark_l(
		mem_input->ctx,
		stutter);

}