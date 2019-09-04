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
struct ov13858 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV13858_REG_B_MWB_GAIN ; 
 int /*<<< orphan*/  OV13858_REG_G_MWB_GAIN ; 
 int /*<<< orphan*/  OV13858_REG_R_MWB_GAIN ; 
 int /*<<< orphan*/  OV13858_REG_VALUE_16BIT ; 
 int ov13858_write_reg (struct ov13858*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov13858_update_digital_gain(struct ov13858 *ov13858, u32 d_gain)
{
	int ret;

	ret = ov13858_write_reg(ov13858, OV13858_REG_B_MWB_GAIN,
				OV13858_REG_VALUE_16BIT, d_gain);
	if (ret)
		return ret;

	ret = ov13858_write_reg(ov13858, OV13858_REG_G_MWB_GAIN,
				OV13858_REG_VALUE_16BIT, d_gain);
	if (ret)
		return ret;

	ret = ov13858_write_reg(ov13858, OV13858_REG_R_MWB_GAIN,
				OV13858_REG_VALUE_16BIT, d_gain);

	return ret;
}