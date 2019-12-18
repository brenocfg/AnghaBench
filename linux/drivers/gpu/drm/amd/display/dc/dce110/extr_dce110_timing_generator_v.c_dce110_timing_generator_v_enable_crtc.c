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

/* Variables and functions */
 int /*<<< orphan*/  CRTCV_MASTER_EN ; 
 int /*<<< orphan*/  CRTCV_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  CRTC_MASTER_EN ; 
 int /*<<< orphan*/  MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTCV_MASTER_EN ; 
 int /*<<< orphan*/  mmCRTCV_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dce110_timing_generator_v_enable_crtc(struct timing_generator *tg)
{
/*
* Set MASTER_UPDATE_MODE to 0
* This is needed for DRR, and also suggested to be default value by Syed.
*/

	uint32_t value;

	value = 0;
	set_reg_field_value(value, 0,
			CRTCV_MASTER_UPDATE_MODE, MASTER_UPDATE_MODE);
	dm_write_reg(tg->ctx,
			mmCRTCV_MASTER_UPDATE_MODE, value);

	/* TODO: may want this on for looking for underflow */
	value = 0;
	dm_write_reg(tg->ctx, mmCRTCV_MASTER_UPDATE_MODE, value);

	value = 0;
	set_reg_field_value(value, 1,
			CRTCV_MASTER_EN, CRTC_MASTER_EN);
	dm_write_reg(tg->ctx,
			mmCRTCV_MASTER_EN, value);

	return true;
}