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
struct stmpe_touch {int ave_ctrl; int touch_det_delay; int settling; int fraction_z; int i_drive; struct device* dev; struct stmpe* stmpe; } ;
struct stmpe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int OP_MOD_XYZ ; 
 int STMPE_AVE_CTRL (int) ; 
 int STMPE_BLOCK_ADC ; 
 int STMPE_BLOCK_TOUCHSCREEN ; 
 int STMPE_DET_DELAY (int) ; 
 int STMPE_FRACTION_Z (int) ; 
 int STMPE_I_DRIVE (int) ; 
 int STMPE_OP_MODE (int) ; 
 int /*<<< orphan*/  STMPE_REG_FIFO_TH ; 
 int /*<<< orphan*/  STMPE_REG_TSC_CFG ; 
 int /*<<< orphan*/  STMPE_REG_TSC_CTRL ; 
 int /*<<< orphan*/  STMPE_REG_TSC_FRACTION_Z ; 
 int /*<<< orphan*/  STMPE_REG_TSC_I_DRIVE ; 
 int STMPE_SETTLING (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int stmpe811_adc_common_init (struct stmpe*) ; 
 int /*<<< orphan*/  stmpe_disable (struct stmpe*,int) ; 
 int stmpe_enable (struct stmpe*,int) ; 
 int stmpe_reg_write (struct stmpe*,int /*<<< orphan*/ ,int) ; 
 int stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stmpe_init_hw(struct stmpe_touch *ts)
{
	int ret;
	u8 tsc_cfg, tsc_cfg_mask;
	struct stmpe *stmpe = ts->stmpe;
	struct device *dev = ts->dev;

	ret = stmpe_enable(stmpe, STMPE_BLOCK_TOUCHSCREEN | STMPE_BLOCK_ADC);
	if (ret) {
		dev_err(dev, "Could not enable clock for ADC and TS\n");
		return ret;
	}

	ret = stmpe811_adc_common_init(stmpe);
	if (ret) {
		stmpe_disable(stmpe, STMPE_BLOCK_TOUCHSCREEN | STMPE_BLOCK_ADC);
		return ret;
	}

	tsc_cfg = STMPE_AVE_CTRL(ts->ave_ctrl) |
		  STMPE_DET_DELAY(ts->touch_det_delay) |
		  STMPE_SETTLING(ts->settling);
	tsc_cfg_mask = STMPE_AVE_CTRL(0xff) | STMPE_DET_DELAY(0xff) |
		       STMPE_SETTLING(0xff);

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_CFG, tsc_cfg_mask, tsc_cfg);
	if (ret) {
		dev_err(dev, "Could not config touch\n");
		return ret;
	}

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_FRACTION_Z,
			STMPE_FRACTION_Z(0xff), STMPE_FRACTION_Z(ts->fraction_z));
	if (ret) {
		dev_err(dev, "Could not config touch\n");
		return ret;
	}

	ret = stmpe_set_bits(stmpe, STMPE_REG_TSC_I_DRIVE,
			STMPE_I_DRIVE(0xff), STMPE_I_DRIVE(ts->i_drive));
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
			STMPE_OP_MODE(0xff), STMPE_OP_MODE(OP_MOD_XYZ));
	if (ret) {
		dev_err(dev, "Could not set mode\n");
		return ret;
	}

	return 0;
}