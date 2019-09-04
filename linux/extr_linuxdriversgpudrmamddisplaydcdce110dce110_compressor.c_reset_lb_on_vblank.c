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
typedef  scalar_t__ uint32_t ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LB_SYNC_RESET_SEL ; 
 int /*<<< orphan*/  LB_SYNC_RESET_SEL2 ; 
 int /*<<< orphan*/  dm_error (char*) ; 
 scalar_t__ dm_read_reg (struct dc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTC_STATUS_FRAME_COUNT ; 
 int /*<<< orphan*/  mmCRTC_STATUS_POSITION ; 
 int /*<<< orphan*/  mmLB_SYNC_RESET_SEL ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void reset_lb_on_vblank(struct dc_context *ctx)
{
	uint32_t value, frame_count;
	uint32_t retry = 0;
	uint32_t status_pos =
			dm_read_reg(ctx, mmCRTC_STATUS_POSITION);


	/* Only if CRTC is enabled and counter is moving we wait for one frame. */
	if (status_pos != dm_read_reg(ctx, mmCRTC_STATUS_POSITION)) {
		/* Resetting LB on VBlank */
		value = dm_read_reg(ctx, mmLB_SYNC_RESET_SEL);
		set_reg_field_value(value, 3, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL);
		set_reg_field_value(value, 1, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL2);
		dm_write_reg(ctx, mmLB_SYNC_RESET_SEL, value);

		frame_count = dm_read_reg(ctx, mmCRTC_STATUS_FRAME_COUNT);


		for (retry = 10000; retry > 0; retry--) {
			if (frame_count != dm_read_reg(ctx, mmCRTC_STATUS_FRAME_COUNT))
				break;
			udelay(10);
		}
		if (!retry)
			dm_error("Frame count did not increase for 100ms.\n");

		/* Resetting LB on VBlank */
		value = dm_read_reg(ctx, mmLB_SYNC_RESET_SEL);
		set_reg_field_value(value, 2, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL);
		set_reg_field_value(value, 0, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL2);
		dm_write_reg(ctx, mmLB_SYNC_RESET_SEL, value);

	}

}