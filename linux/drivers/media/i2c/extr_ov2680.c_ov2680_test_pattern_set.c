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
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  OV2680_REG_ISP_CTRL00 ; 
 int ov2680_mod_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ov2680_test_pattern_set(struct ov2680_dev *sensor, int value)
{
	int ret;

	if (!value)
		return ov2680_mod_reg(sensor, OV2680_REG_ISP_CTRL00, BIT(7), 0);

	ret = ov2680_mod_reg(sensor, OV2680_REG_ISP_CTRL00, 0x03, value - 1);
	if (ret < 0)
		return ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_ISP_CTRL00, BIT(7), BIT(7));
	if (ret < 0)
		return ret;

	return 0;
}