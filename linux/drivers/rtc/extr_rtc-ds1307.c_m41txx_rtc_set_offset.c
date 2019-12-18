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
struct ds1307 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (long,int /*<<< orphan*/ ) ; 
 int ERANGE ; 
 unsigned int M41TXX_BIT_CALIB_SIGN ; 
 long M41TXX_MAX_OFFSET ; 
 long M41TXX_MIN_OFFSET ; 
 unsigned int M41TXX_M_CALIBRATION ; 
 int /*<<< orphan*/  M41TXX_NEG_OFFSET_STEP_PPB ; 
 int /*<<< orphan*/  M41TXX_POS_OFFSET_STEP_PPB ; 
 int /*<<< orphan*/  M41TXX_REG_CONTROL ; 
 long abs (long) ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int m41txx_rtc_set_offset(struct device *dev, long offset)
{
	struct ds1307 *ds1307 = dev_get_drvdata(dev);
	unsigned int ctrl_reg;

	if ((offset < M41TXX_MIN_OFFSET) || (offset > M41TXX_MAX_OFFSET))
		return -ERANGE;

	if (offset >= 0) {
		ctrl_reg = DIV_ROUND_CLOSEST(offset,
					     M41TXX_POS_OFFSET_STEP_PPB);
		ctrl_reg |= M41TXX_BIT_CALIB_SIGN;
	} else {
		ctrl_reg = DIV_ROUND_CLOSEST(abs(offset),
					     M41TXX_NEG_OFFSET_STEP_PPB);
	}

	return regmap_update_bits(ds1307->regmap, M41TXX_REG_CONTROL,
				  M41TXX_M_CALIBRATION | M41TXX_BIT_CALIB_SIGN,
				  ctrl_reg);
}