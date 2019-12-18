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
typedef  int u8 ;
struct cxd2880_tnrdmd {scalar_t__ state; int srl_ts_clk_mod_cnts; int srl_ts_clk_frq; int ts_byte_clk_manual_setting; int is_ts_backwards_compatible_mode; int fixed_clk_mode; int is_cable_input; int en_fef_intmtnt_base; int en_fef_intmtnt_lite; int blind_tune_dvbt2_first; scalar_t__ diver_mode; struct cxd2880_tnrdmd* diver_sub; } ;
typedef  enum cxd2880_tnrdmd_serial_ts_clk { ____Placeholder_cxd2880_tnrdmd_serial_ts_clk } cxd2880_tnrdmd_serial_ts_clk ;
typedef  enum cxd2880_tnrdmd_clockmode { ____Placeholder_cxd2880_tnrdmd_clockmode } cxd2880_tnrdmd_clockmode ;
typedef  enum cxd2880_tnrdmd_cfg_id { ____Placeholder_cxd2880_tnrdmd_cfg_id } cxd2880_tnrdmd_cfg_id ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
#define  CXD2880_TNRDMD_CFG_BLINDTUNE_DVBT2_FIRST 162 
#define  CXD2880_TNRDMD_CFG_CABLE_INPUT 161 
#define  CXD2880_TNRDMD_CFG_DVBT2_BBER_MES 160 
#define  CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_BASE 159 
#define  CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_LITE 158 
#define  CXD2880_TNRDMD_CFG_DVBT2_LBER_MES 157 
#define  CXD2880_TNRDMD_CFG_DVBT2_PER_MES 156 
#define  CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD 155 
#define  CXD2880_TNRDMD_CFG_DVBT_PER_MES 154 
#define  CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD 153 
#define  CXD2880_TNRDMD_CFG_FIXED_CLOCKMODE 152 
#define  CXD2880_TNRDMD_CFG_INTERRUPT 151 
#define  CXD2880_TNRDMD_CFG_INTERRUPT_INV_LOCK_SEL 150 
#define  CXD2880_TNRDMD_CFG_INTERRUPT_LOCK_SEL 149 
#define  CXD2880_TNRDMD_CFG_LATCH_ON_POSEDGE 148 
#define  CXD2880_TNRDMD_CFG_OUTPUT_SEL_MSB 147 
#define  CXD2880_TNRDMD_CFG_PWM_VALUE 146 
#define  CXD2880_TNRDMD_CFG_TSBYTECLK_MANUAL 145 
#define  CXD2880_TNRDMD_CFG_TSCLK_CONT 144 
#define  CXD2880_TNRDMD_CFG_TSCLK_FREQ 143 
#define  CXD2880_TNRDMD_CFG_TSCLK_MASK 142 
#define  CXD2880_TNRDMD_CFG_TSERR_ACTIVE_HI 141 
#define  CXD2880_TNRDMD_CFG_TSERR_MASK 140 
#define  CXD2880_TNRDMD_CFG_TSERR_VALID_DIS 139 
#define  CXD2880_TNRDMD_CFG_TSPIN_CURRENT 138 
#define  CXD2880_TNRDMD_CFG_TSPIN_PULLUP 137 
#define  CXD2880_TNRDMD_CFG_TSPIN_PULLUP_MANUAL 136 
#define  CXD2880_TNRDMD_CFG_TSSYNC_ACTIVE_HI 135 
#define  CXD2880_TNRDMD_CFG_TSVALID_ACTIVE_HI 134 
#define  CXD2880_TNRDMD_CFG_TSVALID_MASK 133 
#define  CXD2880_TNRDMD_CFG_TS_BACKWARDS_COMPATIBLE 132 
#define  CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_EMPTY_THRS 131 
#define  CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_FULL_THRS 130 
#define  CXD2880_TNRDMD_CFG_TS_BUF_RRDY_THRS 129 
#define  CXD2880_TNRDMD_CFG_TS_PACKET_GAP 128 
 int CXD2880_TNRDMD_CLOCKMODE_C ; 
 int CXD2880_TNRDMD_CLOCKMODE_UNKNOWN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_set_and_save_reg_bits (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int,int,int,int) ; 

int cxd2880_tnrdmd_set_cfg(struct cxd2880_tnrdmd *tnr_dmd,
			   enum cxd2880_tnrdmd_cfg_id id,
			   int value)
{
	int ret = 0;
	u8 data[2] = { 0 };
	u8 need_sub_setting = 0;

	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	switch (id) {
	case CXD2880_TNRDMD_CFG_OUTPUT_SEL_MSB:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc4,
							 value ? 0x00 : 0x10,
							 0x10);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSVALID_ACTIVE_HI:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc5,
							 value ? 0x00 : 0x02,
							 0x02);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSSYNC_ACTIVE_HI:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc5,
							 value ? 0x00 : 0x04,
							 0x04);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSERR_ACTIVE_HI:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xcb,
							 value ? 0x00 : 0x01,
							 0x01);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_LATCH_ON_POSEDGE:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc5,
							 value ? 0x01 : 0x00,
							 0x01);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSCLK_CONT:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		tnr_dmd->srl_ts_clk_mod_cnts = value ? 0x01 : 0x00;
		break;

	case CXD2880_TNRDMD_CFG_TSCLK_MASK:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		if (value < 0 || value > 0x1f)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc6, value,
							 0x1f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSVALID_MASK:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		if (value < 0 || value > 0x1f)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc8, value,
							 0x1f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSERR_MASK:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		if (value < 0 || value > 0x1f)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xc9, value,
							 0x1f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSERR_VALID_DIS:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x91,
							 value ? 0x01 : 0x00,
							 0x01);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSPIN_CURRENT:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x51, value,
							 0x3f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSPIN_PULLUP_MANUAL:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x50,
							 value ? 0x80 : 0x00,
							 0x80);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSPIN_PULLUP:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x50, value,
							 0x3f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TSCLK_FREQ:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		if (value < 0 || value > 1)
			return -EINVAL;

		tnr_dmd->srl_ts_clk_frq =
		    (enum cxd2880_tnrdmd_serial_ts_clk)value;
		break;

	case CXD2880_TNRDMD_CFG_TSBYTECLK_MANUAL:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		if (value < 0 || value > 0xff)
			return -EINVAL;

		tnr_dmd->ts_byte_clk_manual_setting = value;

		break;

	case CXD2880_TNRDMD_CFG_TS_PACKET_GAP:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		if (value < 0 || value > 7)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0xd6, value,
							 0x07);
		if (ret)
			return ret;

		break;

	case CXD2880_TNRDMD_CFG_TS_BACKWARDS_COMPATIBLE:
		if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP)
			return -EINVAL;

		tnr_dmd->is_ts_backwards_compatible_mode = value ? 1 : 0;

		break;

	case CXD2880_TNRDMD_CFG_PWM_VALUE:
		if (value < 0 || value > 0x1000)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x22,
							 value ? 0x01 : 0x00,
							 0x01);
		if (ret)
			return ret;

		data[0] = (value >> 8) & 0x1f;
		data[1] = value & 0xff;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x23,
							 data[0], 0x1f);
		if (ret)
			return ret;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x24,
							 data[1], 0xff);
		if (ret)
			return ret;

		break;

	case CXD2880_TNRDMD_CFG_INTERRUPT:
		data[0] = (value >> 8) & 0xff;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x48, data[0],
							 0xff);
		if (ret)
			return ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x49, data[1],
							 0xff);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_INTERRUPT_LOCK_SEL:
		data[0] = value & 0x07;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x4a, data[0],
							 0x07);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_INTERRUPT_INV_LOCK_SEL:
		data[0] = (value & 0x07) << 3;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_SYS,
							 0x00, 0x4a, data[0],
							 0x38);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_FIXED_CLOCKMODE:
		if (value < CXD2880_TNRDMD_CLOCKMODE_UNKNOWN ||
		    value > CXD2880_TNRDMD_CLOCKMODE_C)
			return -EINVAL;
		tnr_dmd->fixed_clk_mode = (enum cxd2880_tnrdmd_clockmode)value;
		break;

	case CXD2880_TNRDMD_CFG_CABLE_INPUT:
		tnr_dmd->is_cable_input = value ? 1 : 0;
		break;

	case CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_BASE:
		tnr_dmd->en_fef_intmtnt_base = value ? 1 : 0;
		break;

	case CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_LITE:
		tnr_dmd->en_fef_intmtnt_lite = value ? 1 : 0;
		break;

	case CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_EMPTY_THRS:
		data[0] = (value >> 8) & 0x07;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x99, data[0],
							 0x07);
		if (ret)
			return ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9a, data[1],
							 0xff);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_FULL_THRS:
		data[0] = (value >> 8) & 0x07;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9b, data[0],
							 0x07);
		if (ret)
			return ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9c, data[1],
							 0xff);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_TS_BUF_RRDY_THRS:
		data[0] = (value >> 8) & 0x07;
		data[1] = value & 0xff;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9d, data[0],
							 0x07);
		if (ret)
			return ret;
		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x00, 0x9e, data[1],
							 0xff);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_BLINDTUNE_DVBT2_FIRST:
		tnr_dmd->blind_tune_dvbt2_first = value ? 1 : 0;
		break;

	case CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD:
		if (value < 0 || value > 31)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x10, 0x60,
							 value & 0x1f, 0x1f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD:
		if (value < 0 || value > 7)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x10, 0x6f,
							 value & 0x07, 0x07);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_DVBT2_BBER_MES:
		if (value < 0 || value > 15)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x20, 0x72,
							 value & 0x0f, 0x0f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_DVBT2_LBER_MES:
		if (value < 0 || value > 15)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x20, 0x6f,
							 value & 0x0f, 0x0f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_DVBT_PER_MES:
		if (value < 0 || value > 15)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x10, 0x5c,
							 value & 0x0f, 0x0f);
		if (ret)
			return ret;
		break;

	case CXD2880_TNRDMD_CFG_DVBT2_PER_MES:
		if (value < 0 || value > 15)
			return -EINVAL;

		ret =
		    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
							 CXD2880_IO_TGT_DMD,
							 0x24, 0xdc,
							 value & 0x0f, 0x0f);
		if (ret)
			return ret;
		break;

	default:
		return -EINVAL;
	}

	if (need_sub_setting &&
	    tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_MAIN)
		ret = cxd2880_tnrdmd_set_cfg(tnr_dmd->diver_sub, id, value);

	return ret;
}