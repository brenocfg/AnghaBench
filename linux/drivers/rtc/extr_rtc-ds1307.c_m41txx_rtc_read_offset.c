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
typedef  long u8 ;
struct ds1307 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int M41TXX_BIT_CALIB_SIGN ; 
 unsigned int M41TXX_M_CALIBRATION ; 
 long M41TXX_NEG_OFFSET_STEP_PPB ; 
 long M41TXX_POS_OFFSET_STEP_PPB ; 
 int /*<<< orphan*/  M41TXX_REG_CONTROL ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int m41txx_rtc_read_offset(struct device *dev, long *offset)
{
	struct ds1307 *ds1307 = dev_get_drvdata(dev);
	unsigned int ctrl_reg;
	u8 val;

	regmap_read(ds1307->regmap, M41TXX_REG_CONTROL, &ctrl_reg);

	val = ctrl_reg & M41TXX_M_CALIBRATION;

	/* check if positive */
	if (ctrl_reg & M41TXX_BIT_CALIB_SIGN)
		*offset = (val * M41TXX_POS_OFFSET_STEP_PPB);
	else
		*offset = -(val * M41TXX_NEG_OFFSET_STEP_PPB);

	return 0;
}