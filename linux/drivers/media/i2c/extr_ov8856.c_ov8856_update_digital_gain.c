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
struct ov8856 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV8856_REG_MWB_B_GAIN ; 
 int /*<<< orphan*/  OV8856_REG_MWB_G_GAIN ; 
 int /*<<< orphan*/  OV8856_REG_MWB_R_GAIN ; 
 int /*<<< orphan*/  OV8856_REG_VALUE_16BIT ; 
 int ov8856_write_reg (struct ov8856*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov8856_update_digital_gain(struct ov8856 *ov8856, u32 d_gain)
{
	int ret;

	ret = ov8856_write_reg(ov8856, OV8856_REG_MWB_R_GAIN,
			       OV8856_REG_VALUE_16BIT, d_gain);
	if (ret)
		return ret;

	ret = ov8856_write_reg(ov8856, OV8856_REG_MWB_G_GAIN,
			       OV8856_REG_VALUE_16BIT, d_gain);
	if (ret)
		return ret;

	return ov8856_write_reg(ov8856, OV8856_REG_MWB_B_GAIN,
				OV8856_REG_VALUE_16BIT, d_gain);
}