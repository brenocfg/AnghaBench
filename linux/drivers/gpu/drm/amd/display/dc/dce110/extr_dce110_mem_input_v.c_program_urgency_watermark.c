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
struct dce_watermarks {int a_mark; int b_mark; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPGV0_PIPE_URGENCY_CONTROL ; 
 int /*<<< orphan*/  DPGV0_WATERMARK_MASK_CONTROL ; 
 int /*<<< orphan*/  URGENCY_HIGH_WATERMARK ; 
 int /*<<< orphan*/  URGENCY_LOW_WATERMARK ; 
 int /*<<< orphan*/  URGENCY_WATERMARK_MASK ; 
 int dm_read_reg (struct dc_context const*,int const) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context const*,int const,int) ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_urgency_watermark(
	const struct dc_context *ctx,
	const uint32_t urgency_addr,
	const uint32_t wm_addr,
	struct dce_watermarks marks_low,
	uint32_t total_dest_line_time_ns)
{
	/* register value */
	uint32_t urgency_cntl = 0;
	uint32_t wm_mask_cntl = 0;

	/*Write mask to enable reading/writing of watermark set A*/
	wm_mask_cntl = dm_read_reg(ctx, wm_addr);
	set_reg_field_value(wm_mask_cntl,
			1,
			DPGV0_WATERMARK_MASK_CONTROL,
			URGENCY_WATERMARK_MASK);
	dm_write_reg(ctx, wm_addr, wm_mask_cntl);

	urgency_cntl = dm_read_reg(ctx, urgency_addr);

	set_reg_field_value(
		urgency_cntl,
		marks_low.a_mark,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_LOW_WATERMARK);

	set_reg_field_value(
		urgency_cntl,
		total_dest_line_time_ns,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_HIGH_WATERMARK);
	dm_write_reg(ctx, urgency_addr, urgency_cntl);

	/*Write mask to enable reading/writing of watermark set B*/
	wm_mask_cntl = dm_read_reg(ctx, wm_addr);
	set_reg_field_value(wm_mask_cntl,
			2,
			DPGV0_WATERMARK_MASK_CONTROL,
			URGENCY_WATERMARK_MASK);
	dm_write_reg(ctx, wm_addr, wm_mask_cntl);

	urgency_cntl = dm_read_reg(ctx, urgency_addr);

	set_reg_field_value(urgency_cntl,
		marks_low.b_mark,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_LOW_WATERMARK);

	set_reg_field_value(urgency_cntl,
		total_dest_line_time_ns,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_HIGH_WATERMARK);

	dm_write_reg(ctx, urgency_addr, urgency_cntl);
}