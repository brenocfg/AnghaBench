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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 unsigned long TPS80031_EXT_PWR_REQ ; 
 int TPS80031_PHOENIX_MSK_TRANSITION ; 
 int TPS80031_PREQ1_RES_ASS_A ; 
 int TPS80031_PREQ2_RES_ASS_A ; 
 int TPS80031_PREQ3_RES_ASS_A ; 
 unsigned long TPS80031_PWR_REQ_INPUT_PREQ1 ; 
 unsigned long TPS80031_PWR_REQ_INPUT_PREQ2 ; 
 unsigned long TPS80031_PWR_REQ_INPUT_PREQ3 ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 int /*<<< orphan*/  TPS80031_STATE_MASK ; 
 int /*<<< orphan*/  TPS80031_TRANS_SLEEP_MASK ; 
 int TPS80031_TRANS_SLEEP_OFF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int tps80031_clr_bits (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int tps80031_set_bits (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int tps80031_update (struct device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int tps80031_ext_power_req_config(struct device *dev,
		unsigned long ext_ctrl_flag, int preq_bit,
		int state_reg_add, int trans_reg_add)
{
	u8 res_ass_reg = 0;
	int preq_mask_bit = 0;
	int ret;

	if (!(ext_ctrl_flag & TPS80031_EXT_PWR_REQ))
		return 0;

	if (ext_ctrl_flag & TPS80031_PWR_REQ_INPUT_PREQ1) {
		res_ass_reg = TPS80031_PREQ1_RES_ASS_A + (preq_bit >> 3);
		preq_mask_bit = 5;
	} else if (ext_ctrl_flag & TPS80031_PWR_REQ_INPUT_PREQ2) {
		res_ass_reg = TPS80031_PREQ2_RES_ASS_A + (preq_bit >> 3);
		preq_mask_bit = 6;
	} else if (ext_ctrl_flag & TPS80031_PWR_REQ_INPUT_PREQ3) {
		res_ass_reg = TPS80031_PREQ3_RES_ASS_A + (preq_bit >> 3);
		preq_mask_bit = 7;
	}

	/* Configure REQ_ASS registers */
	ret = tps80031_set_bits(dev, TPS80031_SLAVE_ID1, res_ass_reg,
					BIT(preq_bit & 0x7));
	if (ret < 0) {
		dev_err(dev, "reg 0x%02x setbit failed, err = %d\n",
				res_ass_reg, ret);
		return ret;
	}

	/* Unmask the PREQ */
	ret = tps80031_clr_bits(dev, TPS80031_SLAVE_ID1,
			TPS80031_PHOENIX_MSK_TRANSITION, BIT(preq_mask_bit));
	if (ret < 0) {
		dev_err(dev, "reg 0x%02x clrbit failed, err = %d\n",
			TPS80031_PHOENIX_MSK_TRANSITION, ret);
		return ret;
	}

	/* Switch regulator control to resource now */
	if (ext_ctrl_flag & (TPS80031_PWR_REQ_INPUT_PREQ2 |
					TPS80031_PWR_REQ_INPUT_PREQ3)) {
		ret = tps80031_update(dev, TPS80031_SLAVE_ID1, state_reg_add,
						0x0, TPS80031_STATE_MASK);
		if (ret < 0)
			dev_err(dev, "reg 0x%02x update failed, err = %d\n",
				state_reg_add, ret);
	} else {
		ret = tps80031_update(dev, TPS80031_SLAVE_ID1, trans_reg_add,
				TPS80031_TRANS_SLEEP_OFF,
				TPS80031_TRANS_SLEEP_MASK);
		if (ret < 0)
			dev_err(dev, "reg 0x%02x update failed, err = %d\n",
				trans_reg_add, ret);
	}
	return ret;
}