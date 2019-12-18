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
typedef  size_t uint32_t ;
struct dce110_compressor {int /*<<< orphan*/  offsets; } ;
struct compressor {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCP_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_SYNC_RESET_SEL ; 
 int /*<<< orphan*/  LB_SYNC_RESET_SEL2 ; 
 struct dce110_compressor* TO_DCE110_COMPRESSOR (struct compressor*) ; 
 int /*<<< orphan*/  dm_error (char*) ; 
 size_t dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mmCRTC_STATUS_FRAME_COUNT ; 
 int /*<<< orphan*/  mmCRTC_STATUS_POSITION ; 
 int /*<<< orphan*/  mmLB_SYNC_RESET_SEL ; 
 int /*<<< orphan*/ * reg_offsets ; 
 int /*<<< orphan*/  set_reg_field_value (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void reset_lb_on_vblank(struct compressor *compressor, uint32_t crtc_inst)
{
	uint32_t value;
	uint32_t frame_count;
	uint32_t status_pos;
	uint32_t retry = 0;
	struct dce110_compressor *cp110 = TO_DCE110_COMPRESSOR(compressor);

	cp110->offsets = reg_offsets[crtc_inst];

	status_pos = dm_read_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_POSITION));


	/* Only if CRTC is enabled and counter is moving we wait for one frame. */
	if (status_pos != dm_read_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_POSITION))) {
		/* Resetting LB on VBlank */
		value = dm_read_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL));
		set_reg_field_value(value, 3, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL);
		set_reg_field_value(value, 1, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL2);
		dm_write_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL), value);

		frame_count = dm_read_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_FRAME_COUNT));


		for (retry = 10000; retry > 0; retry--) {
			if (frame_count != dm_read_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_FRAME_COUNT)))
				break;
			udelay(10);
		}
		if (!retry)
			dm_error("Frame count did not increase for 100ms.\n");

		/* Resetting LB on VBlank */
		value = dm_read_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL));
		set_reg_field_value(value, 2, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL);
		set_reg_field_value(value, 0, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL2);
		dm_write_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL), value);
	}
}