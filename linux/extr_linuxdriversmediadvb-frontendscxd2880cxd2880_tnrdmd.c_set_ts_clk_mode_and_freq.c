#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {int member_0; int member_1; int member_2; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; } ;
struct cxd2880_tnrdmd_ts_clk_cfg {int ts_clk_period; int srl_clk_mode; int srl_duty_mode; TYPE_2__ member_1; TYPE_1__ member_0; } ;
struct cxd2880_tnrdmd {int ts_byte_clk_manual_setting; size_t srl_ts_clk_mod_cnts; size_t srl_ts_clk_frq; TYPE_3__* io; scalar_t__ is_ts_backwards_compatible_mode; } ;
typedef  enum cxd2880_dtv_sys { ____Placeholder_cxd2880_dtv_sys } cxd2880_dtv_sys ;
struct TYPE_9__ {int (* write_reg ) (TYPE_3__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int CXD2880_DTV_SYS_DVBT ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int EINVAL ; 
 int cxd2880_io_set_reg_bits (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int set_ts_clk_mode_and_freq(struct cxd2880_tnrdmd *tnr_dmd,
				    enum cxd2880_dtv_sys sys)
{
	int ret;
	u8 backwards_compatible = 0;
	struct cxd2880_tnrdmd_ts_clk_cfg ts_clk_cfg;
	u8 ts_rate_ctrl_off = 0;
	u8 ts_in_off = 0;
	u8 ts_clk_manaul_on = 0;
	u8 data = 0;

	static const struct cxd2880_tnrdmd_ts_clk_cfg srl_ts_clk_stgs[2][2] = {
		{
			{3, 1, 8,},
			{0, 2, 16,}
		}, {
			{1, 1, 8,},
			{2, 2, 16,}
		}
	};

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	if (ret)
		return ret;

	if (tnr_dmd->is_ts_backwards_compatible_mode) {
		backwards_compatible = 1;
		ts_rate_ctrl_off = 1;
		ts_in_off = 1;
	} else {
		backwards_compatible = 0;
		ts_rate_ctrl_off = 0;
		ts_in_off = 0;
	}

	if (tnr_dmd->ts_byte_clk_manual_setting) {
		ts_clk_manaul_on = 1;
		ts_rate_ctrl_off = 0;
	}

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xd3, ts_rate_ctrl_off, 0x01);
	if (ret)
		return ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xde, ts_in_off, 0x01);
	if (ret)
		return ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xda, ts_clk_manaul_on, 0x01);
	if (ret)
		return ret;

	ts_clk_cfg = srl_ts_clk_stgs[tnr_dmd->srl_ts_clk_mod_cnts]
				    [tnr_dmd->srl_ts_clk_frq];

	if (tnr_dmd->ts_byte_clk_manual_setting)
		ts_clk_cfg.ts_clk_period = tnr_dmd->ts_byte_clk_manual_setting;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xc4, ts_clk_cfg.srl_clk_mode, 0x03);
	if (ret)
		return ret;

	ret = cxd2880_io_set_reg_bits(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xd1, ts_clk_cfg.srl_duty_mode, 0x03);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD, 0xd9,
				     ts_clk_cfg.ts_clk_period);
	if (ret)
		return ret;

	data = backwards_compatible ? 0x00 : 0x01;

	if (sys == CXD2880_DTV_SYS_DVBT) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x10);
		if (ret)
			return ret;

		ret =
		    cxd2880_io_set_reg_bits(tnr_dmd->io,
					    CXD2880_IO_TGT_DMD,
					    0x66, data, 0x01);
	}

	return ret;
}