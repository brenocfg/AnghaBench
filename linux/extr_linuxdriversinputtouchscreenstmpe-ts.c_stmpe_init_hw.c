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
struct stmpe_touch {int sample_time; int mod_12b; int ref_sel; int adc_freq; int ave_ctrl; int touch_det_delay; int settling; int fraction_z; int i_drive; struct device* dev; struct stmpe* stmpe; } ;
struct stmpe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ADC_FREQ (int) ; 
 int AVE_CTRL (int) ; 
 int DET_DELAY (int) ; 
 int FRACTION_Z (int) ; 
 int I_DRIVE (int) ; 
 int MOD_12B (int) ; 
 int OP_MODE (int) ; 
 int OP_MOD_XYZ ; 
 int REF_SEL (int) ; 
 int SAMPLE_TIME (int) ; 
 int SETTLING (int) ; 
 int STMPE_BLOCK_ADC ; 
 int STMPE_BLOCK_TOUCHSCREEN ; 
 int /*<<< orphan*/  STMPE_REG_ADC_CTRL1 ; 
 int /*<<< orphan*/  STMPE_REG_ADC_CTRL2 ; 
 int /*<<< orphan*/  STMPE_REG_FIFO_TH ; 
 int /*<<< orphan*/  STMPE_REG_TSC_CFG ; 
 int /*<<< orphan*/  STMPE_REG_TSC_CTRL ; 
 int /*<<< orphan*/  STMPE_REG_TSC_FRACTION_Z ; 
 int /*<<< orphan*/  STMPE_REG_TSC_I_DRIVE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int stmpe_enable (struct stmpe*,int) ; 
 int stmpe_reg_write (struct stmpe*,int /*<<< orphan*/ ,int) ; 
 int stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stmpe_init_hw(struct stmpe_touch *ts)
{
	int ret;
	u8 adc_ctrl1, adc_ctrl1_mask, tsc_cfg, tsc_cfg_mask;
	struct stmpe *stmpe = ts->stmpe;
	struct device *dev = ts->dev;

	ret = stmpe_enable(stmpe, STMPE_BLOCK_TOUCHSCREEN | STMPE_BLOCK_ADC);
	if (ret) {
		dev_err(dev, "Could not enable clock for ADC and TS\n");
		return ret;
	}

	adc_ctrl1 = SAMPLE_TIME(ts->sample_time) | MOD_12B(ts->mod_12b) |
		REF_SEL(ts->ref_sel);
	adc_ctrl1_mask = SAMPLE_TIME(0xff) | MOD_12B(0xff) | REF_SEL(0xff);

	ret = stmpe_set_bits(stmpe, STMPE_REG_ADC_CTRL1,
			adc_ctrl1_mask, adc_ctrl1);
	if (ret) {
		dev_err(dev, "Could not setup ADC\n");
		return ret;
	}

	ret = stmpe_set_bits(stmpe, STMPE_REG_ADC_CTRL2,
			ADC_FREQ(0xff), ADC_FREQ(ts->adc_freq));
	if (ret) {
		dev_err(dev, "Could not setup ADC\n");
		return ret;
	}

	tsc_cfg = AVE_CTRL(ts->ave_ctrl) | DET_DELAY(ts->touch_det_delay) |
			SETTLING(ts->settling);
	tsc_cfg_mask = AVE_CTRL(0xff) | DET_DELAY(0xff) | SETTLING(0xff);

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_CFG, tsc_cfg_mask, tsc_cfg);
	if (ret) {
		dev_err(dev, "Could not config touch\n");
		return ret;
	}

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_FRACTION_Z,
			FRACTION_Z(0xff), FRACTION_Z(ts->fraction_z));
	if (ret) {
		dev_err(dev, "Could not config touch\n");
		return ret;
	}

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_I_DRIVE,
			I_DRIVE(0xff), I_DRIVE(ts->i_drive));
	if (ret) {
		dev_err(dev, "Could not config touch\n");
		return ret;
	}

	/* set FIFO to 1 for single point reading */
	ret = stmpe_reg_write(stmpe, STMPE_REG_FIFO_TH, 1);
	if (ret) {
		dev_err(dev, "Could not set FIFO\n");
		return ret;
	}

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_CTRL,
			OP_MODE(0xff), OP_MODE(OP_MOD_XYZ));
	if (ret) {
		dev_err(dev, "Could not set mode\n");
		return ret;
	}

	return 0;
}