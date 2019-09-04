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
typedef  int u8 ;
struct lgdt3306a_state {TYPE_1__* cfg; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;
struct TYPE_2__ {int xtalMHz; int /*<<< orphan*/  mpeg_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*) ; 
 scalar_t__ lg_chkerr (int) ; 
 int lgdt3306a_mpeg_mode (struct lgdt3306a_state*,int /*<<< orphan*/ ) ; 
 int lgdt3306a_mpeg_tristate (struct lgdt3306a_state*,int) ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 
 int lgdt3306a_set_inversion (struct lgdt3306a_state*,int) ; 
 int lgdt3306a_set_inversion_auto (struct lgdt3306a_state*,int /*<<< orphan*/ ) ; 
 int lgdt3306a_set_reg_bit (struct lgdt3306a_state*,int,int,int) ; 
 int lgdt3306a_set_vsb (struct lgdt3306a_state*) ; 
 int lgdt3306a_sleep (struct lgdt3306a_state*) ; 
 int lgdt3306a_write_reg (struct lgdt3306a_state*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int lgdt3306a_init(struct dvb_frontend *fe)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;
	u8 val;
	int ret;

	dbg_info("\n");

	/* 1. Normal operation mode */
	ret = lgdt3306a_set_reg_bit(state, 0x0001, 0, 1); /* SIMFASTENB=0x01 */
	if (lg_chkerr(ret))
		goto fail;

	/* 2. Spectrum inversion auto detection (Not valid for VSB) */
	ret = lgdt3306a_set_inversion_auto(state, 0);
	if (lg_chkerr(ret))
		goto fail;

	/* 3. Spectrum inversion(According to the tuner configuration) */
	ret = lgdt3306a_set_inversion(state, 1);
	if (lg_chkerr(ret))
		goto fail;

	/* 4. Peak-to-peak voltage of ADC input signal */

	/* ADCSEL1V=0x80=1Vpp; 0x00=2Vpp */
	ret = lgdt3306a_set_reg_bit(state, 0x0004, 7, 1);
	if (lg_chkerr(ret))
		goto fail;

	/* 5. ADC output data capture clock phase */

	/* 0=same phase as ADC clock */
	ret = lgdt3306a_set_reg_bit(state, 0x0004, 2, 0);
	if (lg_chkerr(ret))
		goto fail;

	/* 5a. ADC sampling clock source */

	/* ADCCLKPLLSEL=0x08; 0=use ext clock, not PLL */
	ret = lgdt3306a_set_reg_bit(state, 0x0004, 3, 0);
	if (lg_chkerr(ret))
		goto fail;

	/* 6. Automatic PLL set */

	/* PLLSETAUTO=0x40; 0=off */
	ret = lgdt3306a_set_reg_bit(state, 0x0005, 6, 0);
	if (lg_chkerr(ret))
		goto fail;

	if (state->cfg->xtalMHz == 24) {	/* 24MHz */
		/* 7. Frequency for PLL output(0x2564 for 192MHz for 24MHz) */
		ret = lgdt3306a_read_reg(state, 0x0005, &val);
		if (lg_chkerr(ret))
			goto fail;
		val &= 0xc0;
		val |= 0x25;
		ret = lgdt3306a_write_reg(state, 0x0005, val);
		if (lg_chkerr(ret))
			goto fail;
		ret = lgdt3306a_write_reg(state, 0x0006, 0x64);
		if (lg_chkerr(ret))
			goto fail;

		/* 8. ADC sampling frequency(0x180000 for 24MHz sampling) */
		ret = lgdt3306a_read_reg(state, 0x000d, &val);
		if (lg_chkerr(ret))
			goto fail;
		val &= 0xc0;
		val |= 0x18;
		ret = lgdt3306a_write_reg(state, 0x000d, val);
		if (lg_chkerr(ret))
			goto fail;

	} else if (state->cfg->xtalMHz == 25) { /* 25MHz */
		/* 7. Frequency for PLL output */
		ret = lgdt3306a_read_reg(state, 0x0005, &val);
		if (lg_chkerr(ret))
			goto fail;
		val &= 0xc0;
		val |= 0x25;
		ret = lgdt3306a_write_reg(state, 0x0005, val);
		if (lg_chkerr(ret))
			goto fail;
		ret = lgdt3306a_write_reg(state, 0x0006, 0x64);
		if (lg_chkerr(ret))
			goto fail;

		/* 8. ADC sampling frequency(0x190000 for 25MHz sampling) */
		ret = lgdt3306a_read_reg(state, 0x000d, &val);
		if (lg_chkerr(ret))
			goto fail;
		val &= 0xc0;
		val |= 0x19;
		ret = lgdt3306a_write_reg(state, 0x000d, val);
		if (lg_chkerr(ret))
			goto fail;
	} else {
		pr_err("Bad xtalMHz=%d\n", state->cfg->xtalMHz);
	}
#if 0
	ret = lgdt3306a_write_reg(state, 0x000e, 0x00);
	ret = lgdt3306a_write_reg(state, 0x000f, 0x00);
#endif

	/* 9. Center frequency of input signal of ADC */
	ret = lgdt3306a_write_reg(state, 0x0010, 0x34); /* 3.25MHz */
	ret = lgdt3306a_write_reg(state, 0x0011, 0x00);

	/* 10. Fixed gain error value */
	ret = lgdt3306a_write_reg(state, 0x0014, 0); /* gain error=0 */

	/* 10a. VSB TR BW gear shift initial step */
	ret = lgdt3306a_read_reg(state, 0x103c, &val);
	val &= 0x0f;
	val |= 0x20; /* SAMGSAUTOSTL_V[3:0] = 2 */
	ret = lgdt3306a_write_reg(state, 0x103c, val);

	/* 10b. Timing offset calibration in low temperature for VSB */
	ret = lgdt3306a_read_reg(state, 0x103d, &val);
	val &= 0xfc;
	val |= 0x03;
	ret = lgdt3306a_write_reg(state, 0x103d, val);

	/* 10c. Timing offset calibration in low temperature for QAM */
	ret = lgdt3306a_read_reg(state, 0x1036, &val);
	val &= 0xf0;
	val |= 0x0c;
	ret = lgdt3306a_write_reg(state, 0x1036, val);

	/* 11. Using the imaginary part of CIR in CIR loading */
	ret = lgdt3306a_read_reg(state, 0x211f, &val);
	val &= 0xef; /* do not use imaginary of CIR */
	ret = lgdt3306a_write_reg(state, 0x211f, val);

	/* 12. Control of no signal detector function */
	ret = lgdt3306a_read_reg(state, 0x2849, &val);
	val &= 0xef; /* NOUSENOSIGDET=0, enable no signal detector */
	ret = lgdt3306a_write_reg(state, 0x2849, val);

	/* FGR - put demod in some known mode */
	ret = lgdt3306a_set_vsb(state);

	/* 13. TP stream format */
	ret = lgdt3306a_mpeg_mode(state, state->cfg->mpeg_mode);

	/* 14. disable output buses */
	ret = lgdt3306a_mpeg_tristate(state, 1);

	/* 15. Sleep (in reset) */
	ret = lgdt3306a_sleep(state);
	lg_chkerr(ret);

fail:
	return ret;
}