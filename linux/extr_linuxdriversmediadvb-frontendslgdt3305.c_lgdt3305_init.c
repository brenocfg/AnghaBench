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
struct lgdt3305_state {TYPE_1__* cfg; } ;
struct lgdt3305_reg {int reg; int val; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;
struct TYPE_2__ {int demod_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct lgdt3305_reg*) ; 
 int EINVAL ; 
#define  LGDT3304 153 
#define  LGDT3305 152 
#define  LGDT3305_AGC_CTRL_1 151 
#define  LGDT3305_AGC_CTRL_4 150 
#define  LGDT3305_AGC_DELAY_PT_1 149 
#define  LGDT3305_AGC_DELAY_PT_2 148 
#define  LGDT3305_AGC_POWER_REF_1 147 
#define  LGDT3305_AGC_POWER_REF_2 146 
#define  LGDT3305_CR_CTRL_7 145 
#define  LGDT3305_CR_CTR_FREQ_1 144 
#define  LGDT3305_CR_CTR_FREQ_2 143 
#define  LGDT3305_CR_CTR_FREQ_3 142 
#define  LGDT3305_CR_CTR_FREQ_4 141 
#define  LGDT3305_DGTL_AGC_REF_1 140 
#define  LGDT3305_DGTL_AGC_REF_2 139 
#define  LGDT3305_FEC_BLOCK_CTRL 138 
#define  LGDT3305_GEN_CONTROL 137 
#define  LGDT3305_GEN_CTRL_1 136 
#define  LGDT3305_GEN_CTRL_2 135 
#define  LGDT3305_GEN_CTRL_3 134 
#define  LGDT3305_GEN_CTRL_4 133 
#define  LGDT3305_IFBW_1 132 
#define  LGDT3305_IFBW_2 131 
#define  LGDT3305_RFAGC_LOOP_FLTR_BW_1 130 
#define  LGDT3305_RFAGC_LOOP_FLTR_BW_2 129 
#define  LGDT3305_TP_CTRL_1 128 
 int /*<<< orphan*/  lg_dbg (char*) ; 
 scalar_t__ lg_fail (int) ; 
 int lgdt3305_soft_reset (struct lgdt3305_state*) ; 
 int lgdt3305_write_regs (struct lgdt3305_state*,struct lgdt3305_reg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lgdt3305_init(struct dvb_frontend *fe)
{
	struct lgdt3305_state *state = fe->demodulator_priv;
	int ret;

	static struct lgdt3305_reg lgdt3304_init_data[] = {
		{ .reg = LGDT3305_GEN_CTRL_1,           .val = 0x03, },
		{ .reg = 0x000d,                        .val = 0x02, },
		{ .reg = 0x000e,                        .val = 0x02, },
		{ .reg = LGDT3305_DGTL_AGC_REF_1,       .val = 0x32, },
		{ .reg = LGDT3305_DGTL_AGC_REF_2,       .val = 0xc4, },
		{ .reg = LGDT3305_CR_CTR_FREQ_1,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTR_FREQ_2,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTR_FREQ_3,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTR_FREQ_4,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTRL_7,            .val = 0xf9, },
		{ .reg = 0x0112,                        .val = 0x17, },
		{ .reg = 0x0113,                        .val = 0x15, },
		{ .reg = 0x0114,                        .val = 0x18, },
		{ .reg = 0x0115,                        .val = 0xff, },
		{ .reg = 0x0116,                        .val = 0x3c, },
		{ .reg = 0x0214,                        .val = 0x67, },
		{ .reg = 0x0424,                        .val = 0x8d, },
		{ .reg = 0x0427,                        .val = 0x12, },
		{ .reg = 0x0428,                        .val = 0x4f, },
		{ .reg = LGDT3305_IFBW_1,               .val = 0x80, },
		{ .reg = LGDT3305_IFBW_2,               .val = 0x00, },
		{ .reg = 0x030a,                        .val = 0x08, },
		{ .reg = 0x030b,                        .val = 0x9b, },
		{ .reg = 0x030d,                        .val = 0x00, },
		{ .reg = 0x030e,                        .val = 0x1c, },
		{ .reg = 0x0314,                        .val = 0xe1, },
		{ .reg = 0x000d,                        .val = 0x82, },
		{ .reg = LGDT3305_TP_CTRL_1,            .val = 0x5b, },
		{ .reg = LGDT3305_TP_CTRL_1,            .val = 0x5b, },
	};

	static struct lgdt3305_reg lgdt3305_init_data[] = {
		{ .reg = LGDT3305_GEN_CTRL_1,           .val = 0x03, },
		{ .reg = LGDT3305_GEN_CTRL_2,           .val = 0xb0, },
		{ .reg = LGDT3305_GEN_CTRL_3,           .val = 0x01, },
		{ .reg = LGDT3305_GEN_CONTROL,          .val = 0x6f, },
		{ .reg = LGDT3305_GEN_CTRL_4,           .val = 0x03, },
		{ .reg = LGDT3305_DGTL_AGC_REF_1,       .val = 0x32, },
		{ .reg = LGDT3305_DGTL_AGC_REF_2,       .val = 0xc4, },
		{ .reg = LGDT3305_CR_CTR_FREQ_1,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTR_FREQ_2,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTR_FREQ_3,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTR_FREQ_4,        .val = 0x00, },
		{ .reg = LGDT3305_CR_CTRL_7,            .val = 0x79, },
		{ .reg = LGDT3305_AGC_POWER_REF_1,      .val = 0x32, },
		{ .reg = LGDT3305_AGC_POWER_REF_2,      .val = 0xc4, },
		{ .reg = LGDT3305_AGC_DELAY_PT_1,       .val = 0x0d, },
		{ .reg = LGDT3305_AGC_DELAY_PT_2,       .val = 0x30, },
		{ .reg = LGDT3305_RFAGC_LOOP_FLTR_BW_1, .val = 0x80, },
		{ .reg = LGDT3305_RFAGC_LOOP_FLTR_BW_2, .val = 0x00, },
		{ .reg = LGDT3305_IFBW_1,               .val = 0x80, },
		{ .reg = LGDT3305_IFBW_2,               .val = 0x00, },
		{ .reg = LGDT3305_AGC_CTRL_1,           .val = 0x30, },
		{ .reg = LGDT3305_AGC_CTRL_4,           .val = 0x61, },
		{ .reg = LGDT3305_FEC_BLOCK_CTRL,       .val = 0xff, },
		{ .reg = LGDT3305_TP_CTRL_1,            .val = 0x1b, },
	};

	lg_dbg("\n");

	switch (state->cfg->demod_chip) {
	case LGDT3304:
		ret = lgdt3305_write_regs(state, lgdt3304_init_data,
					  ARRAY_SIZE(lgdt3304_init_data));
		break;
	case LGDT3305:
		ret = lgdt3305_write_regs(state, lgdt3305_init_data,
					  ARRAY_SIZE(lgdt3305_init_data));
		break;
	default:
		ret = -EINVAL;
	}
	if (lg_fail(ret))
		goto fail;

	ret = lgdt3305_soft_reset(state);
fail:
	return ret;
}