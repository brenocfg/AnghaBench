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
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_GSL_CHECK_LINE_NUM ; 
 int /*<<< orphan*/  CRTC_GSL_CONTROL ; 
 int /*<<< orphan*/  CRTC_GSL_FORCE_DELAY ; 
 scalar_t__ CRTC_REG (int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  DCP_GSL0_EN ; 
 int /*<<< orphan*/  DCP_GSL_CONTROL ; 
 int /*<<< orphan*/  DCP_GSL_DELAY_SURFACE_UPDATE_PENDING ; 
 int /*<<< orphan*/  DCP_GSL_HSYNC_FLIP_CHECK_DELAY ; 
 int /*<<< orphan*/  DCP_GSL_HSYNC_FLIP_FORCE_DELAY ; 
 int /*<<< orphan*/  DCP_GSL_MASTER_EN ; 
 int /*<<< orphan*/  DCP_GSL_SYNC_SOURCE ; 
 scalar_t__ DCP_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_read_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTC_GSL_CONTROL ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL ; 
 int /*<<< orphan*/  mmDCP_GSL_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_timing_generator_tear_down_global_swap_lock(
	struct timing_generator *tg)
{
	/* Clear all the register writes done by
	 * dce110_timing_generator_setup_global_swap_lock
	 */

	uint32_t value;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t address = DCP_REG(mmDCP_GSL_CONTROL);

	value = 0;

	/* This pipe will belong to GSL Group zero. */
	/* Settig HW default values from reg specs */
	set_reg_field_value(value,
			0,
			DCP_GSL_CONTROL,
			DCP_GSL0_EN);

	set_reg_field_value(value,
			0,
			DCP_GSL_CONTROL,
			DCP_GSL_MASTER_EN);

	set_reg_field_value(value,
			0x2,
			DCP_GSL_CONTROL,
			DCP_GSL_HSYNC_FLIP_FORCE_DELAY);

	set_reg_field_value(value,
			0x6,
			DCP_GSL_CONTROL,
			DCP_GSL_HSYNC_FLIP_CHECK_DELAY);

	/* Restore DCP_GSL_PURPOSE_SURFACE_FLIP */
	{
		uint32_t value_crtc_vtotal;

		value_crtc_vtotal = dm_read_reg(tg->ctx,
				CRTC_REG(mmCRTC_V_TOTAL));

		set_reg_field_value(value,
				0,
				DCP_GSL_CONTROL,
				DCP_GSL_SYNC_SOURCE);
	}

	set_reg_field_value(value,
			0,
			DCP_GSL_CONTROL,
			DCP_GSL_DELAY_SURFACE_UPDATE_PENDING);

	dm_write_reg(tg->ctx, address, value);

	/********************************************************************/
	address = CRTC_REG(mmCRTC_GSL_CONTROL);

	value = 0;
	set_reg_field_value(value,
			0,
			CRTC_GSL_CONTROL,
			CRTC_GSL_CHECK_LINE_NUM);

	set_reg_field_value(value,
			0x2,
			CRTC_GSL_CONTROL,
			CRTC_GSL_FORCE_DELAY);

	dm_write_reg(tg->ctx, address, value);
}