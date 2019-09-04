#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mxl5xx_cfg {int ts_clk; int /*<<< orphan*/  cap; int /*<<< orphan*/  clk; } ;
struct mxl {TYPE_1__* base; int /*<<< orphan*/  i2cdev; } ;
struct MXL_HYDRA_MPEGOUT_PARAM_T {int max_mpeg_clk_rate; void* mpeg_valid_pol; int /*<<< orphan*/  mpeg_sync_pulse_width; void* mpeg_sync_pol; int /*<<< orphan*/  mpeg_mode; int /*<<< orphan*/  mpeg_error_indication; int /*<<< orphan*/  mpeg_clk_type; int /*<<< orphan*/  mpeg_clk_pol; int /*<<< orphan*/  mpeg_clk_phase; int /*<<< orphan*/  lsb_or_msb_first; int /*<<< orphan*/  enable; } ;
typedef  enum MXL_HYDRA_DEMOD_ID_E { ____Placeholder_MXL_HYDRA_DEMOD_ID_E } MXL_HYDRA_DEMOD_ID_E ;
struct TYPE_2__ {int type; int can_clkout; int demod_num; int tuner_num; int chan_bond; int chipversion; int /*<<< orphan*/  sku_type; void* ts_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXL_ENABLE ; 
#define  MXL_HYDRA_DEVICE_541 140 
#define  MXL_HYDRA_DEVICE_541S 139 
#define  MXL_HYDRA_DEVICE_542 138 
#define  MXL_HYDRA_DEVICE_544 137 
#define  MXL_HYDRA_DEVICE_561 136 
#define  MXL_HYDRA_DEVICE_561S 135 
#define  MXL_HYDRA_DEVICE_568 134 
#define  MXL_HYDRA_DEVICE_581 133 
#define  MXL_HYDRA_DEVICE_581S 132 
#define  MXL_HYDRA_DEVICE_582 131 
#define  MXL_HYDRA_DEVICE_584 130 
#define  MXL_HYDRA_DEVICE_585 129 
#define  MXL_HYDRA_DEVICE_TEST 128 
 void* MXL_HYDRA_MPEG_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_CLK_CONTINUOUS ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_CLK_IN_PHASE ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_SERIAL_MSB_1ST ; 
 int /*<<< orphan*/  MXL_HYDRA_MPEG_SYNC_WIDTH_BIT ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_541 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_542 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_544 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_561 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_568 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_581 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_582 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_584 ; 
 int /*<<< orphan*/  MXL_HYDRA_SKU_TYPE_585 ; 
 int /*<<< orphan*/  cfg_dev_xtal (struct mxl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_mux (struct mxl*) ; 
 int config_ts (struct mxl*,int,struct MXL_HYDRA_MPEGOUT_PARAM_T*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int firmware_is_alive (struct mxl*) ; 
 int /*<<< orphan*/  get_fwinfo (struct mxl*) ; 
 int load_fw (struct mxl*,struct mxl5xx_cfg*) ; 
 int read_by_mnemonic (struct mxl*,int,int,int,int*) ; 
 int /*<<< orphan*/  set_drive_strength (struct mxl*,int) ; 
 void* ts_map1_to_1 ; 
 void* ts_map54x ; 
 int /*<<< orphan*/  update_by_mnemonic (struct mxl*,int,int,int,int) ; 
 int validate_sku (struct mxl*) ; 

__attribute__((used)) static int probe(struct mxl *state, struct mxl5xx_cfg *cfg)
{
	u32 chipver;
	int fw, status, j;
	struct MXL_HYDRA_MPEGOUT_PARAM_T mpeg_interface_cfg;

	state->base->ts_map = ts_map1_to_1;

	switch (state->base->type) {
	case MXL_HYDRA_DEVICE_581:
	case MXL_HYDRA_DEVICE_581S:
		state->base->can_clkout = 1;
		state->base->demod_num = 8;
		state->base->tuner_num = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_581;
		break;
	case MXL_HYDRA_DEVICE_582:
		state->base->can_clkout = 1;
		state->base->demod_num = 8;
		state->base->tuner_num = 3;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_582;
		break;
	case MXL_HYDRA_DEVICE_585:
		state->base->can_clkout = 0;
		state->base->demod_num = 8;
		state->base->tuner_num = 4;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_585;
		break;
	case MXL_HYDRA_DEVICE_544:
		state->base->can_clkout = 0;
		state->base->demod_num = 4;
		state->base->tuner_num = 4;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_544;
		state->base->ts_map = ts_map54x;
		break;
	case MXL_HYDRA_DEVICE_541:
	case MXL_HYDRA_DEVICE_541S:
		state->base->can_clkout = 0;
		state->base->demod_num = 4;
		state->base->tuner_num = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_541;
		state->base->ts_map = ts_map54x;
		break;
	case MXL_HYDRA_DEVICE_561:
	case MXL_HYDRA_DEVICE_561S:
		state->base->can_clkout = 0;
		state->base->demod_num = 6;
		state->base->tuner_num = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_561;
		break;
	case MXL_HYDRA_DEVICE_568:
		state->base->can_clkout = 0;
		state->base->demod_num = 8;
		state->base->tuner_num = 1;
		state->base->chan_bond = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_568;
		break;
	case MXL_HYDRA_DEVICE_542:
		state->base->can_clkout = 1;
		state->base->demod_num = 4;
		state->base->tuner_num = 3;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_542;
		state->base->ts_map = ts_map54x;
		break;
	case MXL_HYDRA_DEVICE_TEST:
	case MXL_HYDRA_DEVICE_584:
	default:
		state->base->can_clkout = 0;
		state->base->demod_num = 8;
		state->base->tuner_num = 4;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_584;
		break;
	}

	status = validate_sku(state);
	if (status)
		return status;

	update_by_mnemonic(state, 0x80030014, 9, 1, 1);
	update_by_mnemonic(state, 0x8003003C, 12, 1, 1);
	status = read_by_mnemonic(state, 0x80030000, 12, 4, &chipver);
	if (status)
		state->base->chipversion = 0;
	else
		state->base->chipversion = (chipver == 2) ? 2 : 1;
	dev_info(state->i2cdev, "Hydra chip version %u\n",
		state->base->chipversion);

	cfg_dev_xtal(state, cfg->clk, cfg->cap, 0);

	fw = firmware_is_alive(state);
	if (!fw) {
		status = load_fw(state, cfg);
		if (status)
			return status;
	}
	get_fwinfo(state);

	config_mux(state);
	mpeg_interface_cfg.enable = MXL_ENABLE;
	mpeg_interface_cfg.lsb_or_msb_first = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;
	/*  supports only (0-104&139)MHz */
	if (cfg->ts_clk)
		mpeg_interface_cfg.max_mpeg_clk_rate = cfg->ts_clk;
	else
		mpeg_interface_cfg.max_mpeg_clk_rate = 69; /* 139; */
	mpeg_interface_cfg.mpeg_clk_phase = MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG;
	mpeg_interface_cfg.mpeg_clk_pol = MXL_HYDRA_MPEG_CLK_IN_PHASE;
	/* MXL_HYDRA_MPEG_CLK_GAPPED; */
	mpeg_interface_cfg.mpeg_clk_type = MXL_HYDRA_MPEG_CLK_CONTINUOUS;
	mpeg_interface_cfg.mpeg_error_indication =
		MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED;
	mpeg_interface_cfg.mpeg_mode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
	mpeg_interface_cfg.mpeg_sync_pol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;
	mpeg_interface_cfg.mpeg_sync_pulse_width  = MXL_HYDRA_MPEG_SYNC_WIDTH_BIT;
	mpeg_interface_cfg.mpeg_valid_pol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;

	for (j = 0; j < state->base->demod_num; j++) {
		status = config_ts(state, (enum MXL_HYDRA_DEMOD_ID_E) j,
				   &mpeg_interface_cfg);
		if (status)
			return status;
	}
	set_drive_strength(state, 1);
	return 0;
}