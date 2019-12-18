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
typedef  scalar_t__ u32 ;
struct dw_i2c_dev {int sda_hold_time; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_sda_hold_time ) (struct dw_i2c_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_COMP_VERSION ; 
 int /*<<< orphan*/  DW_IC_SDA_HOLD ; 
 scalar_t__ DW_IC_SDA_HOLD_MIN_VERS ; 
 int DW_IC_SDA_HOLD_RX_MASK ; 
 int DW_IC_SDA_HOLD_RX_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int i2c_dw_acquire_lock (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_release_lock (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  stub1 (struct dw_i2c_dev*) ; 

int i2c_dw_set_sda_hold(struct dw_i2c_dev *dev)
{
	u32 reg;
	int ret;

	ret = i2c_dw_acquire_lock(dev);
	if (ret)
		return ret;

	/* Configure SDA Hold Time if required */
	reg = dw_readl(dev, DW_IC_COMP_VERSION);
	if (reg >= DW_IC_SDA_HOLD_MIN_VERS) {
		if (!dev->sda_hold_time) {
			/* Keep previous hold time setting if no one set it */
			dev->sda_hold_time = dw_readl(dev, DW_IC_SDA_HOLD);
		}

		/*
		 * Workaround for avoiding TX arbitration lost in case I2C
		 * slave pulls SDA down "too quickly" after falling egde of
		 * SCL by enabling non-zero SDA RX hold. Specification says it
		 * extends incoming SDA low to high transition while SCL is
		 * high but it apprears to help also above issue.
		 */
		if (!(dev->sda_hold_time & DW_IC_SDA_HOLD_RX_MASK))
			dev->sda_hold_time |= 1 << DW_IC_SDA_HOLD_RX_SHIFT;

		dev_dbg(dev->dev, "SDA Hold Time TX:RX = %d:%d\n",
			dev->sda_hold_time & ~(u32)DW_IC_SDA_HOLD_RX_MASK,
			dev->sda_hold_time >> DW_IC_SDA_HOLD_RX_SHIFT);
	} else if (dev->set_sda_hold_time) {
		dev->set_sda_hold_time(dev);
	} else if (dev->sda_hold_time) {
		dev_warn(dev->dev,
			"Hardware too old to adjust SDA hold time.\n");
		dev->sda_hold_time = 0;
	}

	i2c_dw_release_lock(dev);

	return 0;
}