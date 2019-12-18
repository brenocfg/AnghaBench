#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int CLK_GATING_DISABLED; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct compressor {int /*<<< orphan*/  ctx; int /*<<< orphan*/  min_compress_ratio; TYPE_2__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBC_CNTL ; 
 int /*<<< orphan*/  FBC_COHERENCY_MODE ; 
 int /*<<< orphan*/  FBC_COMPRESS_RATIO_1TO1 ; 
 int /*<<< orphan*/  FBC_COMP_CLK_GATE_EN ; 
 int /*<<< orphan*/  FBC_COMP_CNTL ; 
 int /*<<< orphan*/  FBC_COMP_MODE ; 
 int /*<<< orphan*/  FBC_DEPTH_RGB08_EN ; 
 int /*<<< orphan*/  FBC_DPCM4_RGB_EN ; 
 int /*<<< orphan*/  FBC_EN ; 
 int /*<<< orphan*/  FBC_GRPH_COMP_EN ; 
 int /*<<< orphan*/  FBC_IND_EN ; 
 int /*<<< orphan*/  FBC_MIN_COMPRESSION ; 
 int /*<<< orphan*/  FBC_RLE_EN ; 
 int dm_read_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int,int) ; 
 int mmFBC_CNTL ; 
 int mmFBC_COMP_CNTL ; 
 int mmFBC_COMP_MODE ; 
 int mmFBC_IND_LUT0 ; 
 int mmFBC_IND_LUT1 ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce112_compressor_power_up_fbc(struct compressor *compressor)
{
	uint32_t value;
	uint32_t addr;

	addr = mmFBC_CNTL;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(value, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
	set_reg_field_value(value, 1, FBC_CNTL, FBC_EN);
	set_reg_field_value(value, 2, FBC_CNTL, FBC_COHERENCY_MODE);
	if (compressor->options.bits.CLK_GATING_DISABLED == 1) {
		/* HW needs to do power measurement comparison. */
		set_reg_field_value(
			value,
			0,
			FBC_CNTL,
			FBC_COMP_CLK_GATE_EN);
	}
	dm_write_reg(compressor->ctx, addr, value);

	addr = mmFBC_COMP_MODE;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(value, 1, FBC_COMP_MODE, FBC_RLE_EN);
	set_reg_field_value(value, 1, FBC_COMP_MODE, FBC_DPCM4_RGB_EN);
	set_reg_field_value(value, 1, FBC_COMP_MODE, FBC_IND_EN);
	dm_write_reg(compressor->ctx, addr, value);

	addr = mmFBC_COMP_CNTL;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(value, 1, FBC_COMP_CNTL, FBC_DEPTH_RGB08_EN);
	dm_write_reg(compressor->ctx, addr, value);
	/*FBC_MIN_COMPRESSION 0 ==> 2:1 */
	/*                    1 ==> 4:1 */
	/*                    2 ==> 8:1 */
	/*                  0xF ==> 1:1 */
	set_reg_field_value(value, 0xF, FBC_COMP_CNTL, FBC_MIN_COMPRESSION);
	dm_write_reg(compressor->ctx, addr, value);
	compressor->min_compress_ratio = FBC_COMPRESS_RATIO_1TO1;

	value = 0;
	dm_write_reg(compressor->ctx, mmFBC_IND_LUT0, value);

	value = 0xFFFFFF;
	dm_write_reg(compressor->ctx, mmFBC_IND_LUT1, value);
}