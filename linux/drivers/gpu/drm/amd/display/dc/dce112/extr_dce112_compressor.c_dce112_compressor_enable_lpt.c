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
struct dce112_compressor {int dummy; } ;
struct compressor {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int DMIF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPGV0_PIPE_STUTTER_CONTROL_NONLPTCH ; 
 int /*<<< orphan*/  DPG_PIPE_STUTTER_CONTROL_NONLPTCH ; 
 int /*<<< orphan*/  GMCON_LPT_TARGET ; 
 int /*<<< orphan*/  LOW_POWER_TILING_CONTROL ; 
 int /*<<< orphan*/  LOW_POWER_TILING_ENABLE ; 
 int /*<<< orphan*/  LOW_POWER_TILING_MODE ; 
 int /*<<< orphan*/  STCTRL_LPT_TARGET ; 
 int /*<<< orphan*/  STUTTER_ENABLE_NONLPTCH ; 
 struct dce112_compressor* TO_DCE112_COMPRESSOR (struct compressor*) ; 
 int dm_read_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int,int) ; 
 int get_reg_field_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmDPGV0_PIPE_STUTTER_CONTROL_NONLPTCH ; 
 int /*<<< orphan*/  mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH ; 
 int mmGMCON_LPT_TARGET ; 
 int mmLOW_POWER_TILING_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce112_compressor_enable_lpt(struct compressor *compressor)
{
	struct dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);
	uint32_t value;
	uint32_t addr;
	uint32_t value_control;
	uint32_t channels;

	/* Enable LPT Stutter from Display pipe */
	value = dm_read_reg(compressor->ctx,
		DMIF_REG(mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH));
	set_reg_field_value(
		value,
		1,
		DPG_PIPE_STUTTER_CONTROL_NONLPTCH,
		STUTTER_ENABLE_NONLPTCH);
	dm_write_reg(compressor->ctx,
		DMIF_REG(mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH), value);

	/* Enable Underlay pipe LPT Stutter */
	addr = mmDPGV0_PIPE_STUTTER_CONTROL_NONLPTCH;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_STUTTER_CONTROL_NONLPTCH,
		STUTTER_ENABLE_NONLPTCH);
	dm_write_reg(compressor->ctx, addr, value);

	/* Selection of Channel(s) containing Compressed Surface: 0xfffffff
	 * will disable LPT.
	 * STCTRL_LPT_TARGETn corresponds to channel n. */
	addr = mmLOW_POWER_TILING_CONTROL;
	value_control = dm_read_reg(compressor->ctx, addr);
	channels = get_reg_field_value(value_control,
			LOW_POWER_TILING_CONTROL,
			LOW_POWER_TILING_MODE);

	addr = mmGMCON_LPT_TARGET;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		channels + 1, /* not mentioned in programming guide,
				but follow DCE8.1 */
		GMCON_LPT_TARGET,
		STCTRL_LPT_TARGET);
	dm_write_reg(compressor->ctx, addr, value);

	/* Enable LPT */
	addr = mmLOW_POWER_TILING_CONTROL;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		1,
		LOW_POWER_TILING_CONTROL,
		LOW_POWER_TILING_ENABLE);
	dm_write_reg(compressor->ctx, addr, value);
}