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
struct compressor {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOW_POWER_TILING_CONTROL ; 
 int /*<<< orphan*/  LOW_POWER_TILING_ENABLE ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmLOW_POWER_TILING_CONTROL ; 

bool dce112_compressor_is_lpt_enabled_in_hw(struct compressor *compressor)
{
	/* Check the hardware register */
	uint32_t value = dm_read_reg(compressor->ctx,
		mmLOW_POWER_TILING_CONTROL);

	return get_reg_field_value(
		value,
		LOW_POWER_TILING_CONTROL,
		LOW_POWER_TILING_ENABLE);
}