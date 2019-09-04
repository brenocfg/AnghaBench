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
struct i2caux {int dummy; } ;
struct dc_context {int dce_version; int /*<<< orphan*/  dce_environment; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  DCE_VERSION_10_0 135 
#define  DCE_VERSION_11_0 134 
#define  DCE_VERSION_11_2 133 
#define  DCE_VERSION_11_22 132 
#define  DCE_VERSION_12_0 131 
#define  DCE_VERSION_8_0 130 
#define  DCE_VERSION_8_1 129 
#define  DCE_VERSION_8_3 128 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 struct i2caux* dal_i2caux_dce100_create (struct dc_context*) ; 
 struct i2caux* dal_i2caux_dce110_create (struct dc_context*) ; 
 struct i2caux* dal_i2caux_dce112_create (struct dc_context*) ; 
 struct i2caux* dal_i2caux_dce120_create (struct dc_context*) ; 
 struct i2caux* dal_i2caux_dce80_create (struct dc_context*) ; 
 struct i2caux* dal_i2caux_diag_fpga_create (struct dc_context*) ; 

struct i2caux *dal_i2caux_create(
	struct dc_context *ctx)
{
	if (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) {
		return dal_i2caux_diag_fpga_create(ctx);
	}

	switch (ctx->dce_version) {
	case DCE_VERSION_8_0:
	case DCE_VERSION_8_1:
	case DCE_VERSION_8_3:
		return dal_i2caux_dce80_create(ctx);
	case DCE_VERSION_11_2:
	case DCE_VERSION_11_22:
		return dal_i2caux_dce112_create(ctx);
	case DCE_VERSION_11_0:
		return dal_i2caux_dce110_create(ctx);
	case DCE_VERSION_10_0:
		return dal_i2caux_dce100_create(ctx);
	case DCE_VERSION_12_0:
		return dal_i2caux_dce120_create(ctx);
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case DCN_VERSION_1_0:
		return dal_i2caux_dcn10_create(ctx);
#endif

	default:
		BREAK_TO_DEBUGGER();
		return NULL;
	}
}