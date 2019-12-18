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
typedef  int /*<<< orphan*/  u32 ;
struct imx258 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX258_REG_B_DIGITAL_GAIN ; 
 int /*<<< orphan*/  IMX258_REG_GB_DIGITAL_GAIN ; 
 int /*<<< orphan*/  IMX258_REG_GR_DIGITAL_GAIN ; 
 int /*<<< orphan*/  IMX258_REG_R_DIGITAL_GAIN ; 
 int /*<<< orphan*/  IMX258_REG_VALUE_16BIT ; 
 int imx258_write_reg (struct imx258*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx258_update_digital_gain(struct imx258 *imx258, u32 len, u32 val)
{
	int ret;

	ret = imx258_write_reg(imx258, IMX258_REG_GR_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	if (ret)
		return ret;
	ret = imx258_write_reg(imx258, IMX258_REG_GB_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	if (ret)
		return ret;
	ret = imx258_write_reg(imx258, IMX258_REG_R_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	if (ret)
		return ret;
	ret = imx258_write_reg(imx258, IMX258_REG_B_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	if (ret)
		return ret;
	return 0;
}