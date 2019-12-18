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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct si2165_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct si2165_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_ADDR_JUMP ; 
 int /*<<< orphan*/  REG_GP_REG0_LSB ; 
 int /*<<< orphan*/  REG_RST_ALL ; 
 int /*<<< orphan*/  REG_START_SYNCHRO ; 
 int /*<<< orphan*/  REG_WDOG_AND_BOOT ; 
#define  SYS_DVBC_ANNEX_A 129 
#define  SYS_DVBT 128 
 int /*<<< orphan*/  adc_rewrite ; 
 int si2165_readreg8 (struct si2165_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si2165_set_frontend_dvbc (struct dvb_frontend*) ; 
 int si2165_set_frontend_dvbt (struct dvb_frontend*) ; 
 int si2165_set_if_freq_shift (struct si2165_state*) ; 
 int si2165_write_reg_list (struct si2165_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si2165_writereg32 (struct si2165_state*,int /*<<< orphan*/ ,int) ; 
 int si2165_writereg8 (struct si2165_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int si2165_set_frontend(struct dvb_frontend *fe)
{
	struct si2165_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 delsys = p->delivery_system;
	int ret;
	u8 val[3];

	/* initial setting of if freq shift */
	ret = si2165_set_if_freq_shift(state);
	if (ret < 0)
		return ret;

	switch (delsys) {
	case SYS_DVBT:
		ret = si2165_set_frontend_dvbt(fe);
		if (ret < 0)
			return ret;
		break;
	case SYS_DVBC_ANNEX_A:
		ret = si2165_set_frontend_dvbc(fe);
		if (ret < 0)
			return ret;
		break;
	default:
		return -EINVAL;
	}

	/* dsp_addr_jump */
	ret = si2165_writereg32(state, REG_ADDR_JUMP, 0xf4000000);
	if (ret < 0)
		return ret;

	if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* recalc if_freq_shift if IF might has changed */
	ret = si2165_set_if_freq_shift(state);
	if (ret < 0)
		return ret;

	/* boot/wdog status */
	ret = si2165_readreg8(state, REG_WDOG_AND_BOOT, val);
	if (ret < 0)
		return ret;
	ret = si2165_writereg8(state, REG_WDOG_AND_BOOT, 0x00);
	if (ret < 0)
		return ret;

	/* reset all */
	ret = si2165_writereg8(state, REG_RST_ALL, 0x00);
	if (ret < 0)
		return ret;
	/* gp_reg0 */
	ret = si2165_writereg32(state, REG_GP_REG0_LSB, 0x00000000);
	if (ret < 0)
		return ret;

	/* write adc values after each reset*/
	ret = si2165_write_reg_list(state, adc_rewrite,
				    ARRAY_SIZE(adc_rewrite));
	if (ret < 0)
		return ret;

	/* start_synchro */
	ret = si2165_writereg8(state, REG_START_SYNCHRO, 0x01);
	if (ret < 0)
		return ret;
	/* boot/wdog status */
	ret = si2165_readreg8(state, REG_WDOG_AND_BOOT, val);
	if (ret < 0)
		return ret;

	return 0;
}