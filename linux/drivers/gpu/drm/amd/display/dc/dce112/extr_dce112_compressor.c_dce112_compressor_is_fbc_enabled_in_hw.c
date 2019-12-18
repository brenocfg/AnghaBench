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
struct compressor {int /*<<< orphan*/  attached_inst; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBC_CNTL ; 
 int /*<<< orphan*/  FBC_ENABLE_STATUS ; 
 int /*<<< orphan*/  FBC_GRPH_COMP_EN ; 
 int /*<<< orphan*/  FBC_MISC ; 
 int /*<<< orphan*/  FBC_STATUS ; 
 int /*<<< orphan*/  FBC_STOP_ON_HFLIP_EVENT ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmFBC_CNTL ; 
 int /*<<< orphan*/  mmFBC_MISC ; 
 int /*<<< orphan*/  mmFBC_STATUS ; 

bool dce112_compressor_is_fbc_enabled_in_hw(
	struct compressor *compressor,
	uint32_t *inst)
{
	/* Check the hardware register */
	uint32_t value;

	value = dm_read_reg(compressor->ctx, mmFBC_STATUS);
	if (get_reg_field_value(value, FBC_STATUS, FBC_ENABLE_STATUS)) {
		if (inst != NULL)
			*inst = compressor->attached_inst;
		return true;
	}

	value = dm_read_reg(compressor->ctx, mmFBC_MISC);
	if (get_reg_field_value(value, FBC_MISC, FBC_STOP_ON_HFLIP_EVENT)) {
		value = dm_read_reg(compressor->ctx, mmFBC_CNTL);

		if (get_reg_field_value(value, FBC_CNTL, FBC_GRPH_COMP_EN)) {
			if (inst != NULL)
				*inst =
					compressor->attached_inst;
			return true;
		}
	}
	return false;
}