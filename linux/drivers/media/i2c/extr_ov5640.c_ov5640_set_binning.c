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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OV5640_REG_TIMING_TC_REG20 ; 
 int /*<<< orphan*/  OV5640_REG_TIMING_TC_REG21 ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5640_set_binning(struct ov5640_dev *sensor, bool enable)
{
	int ret;

	/*
	 * TIMING TC REG21:
	 * - [0]:	Horizontal binning enable
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG21,
			     BIT(0), enable ? BIT(0) : 0);
	if (ret)
		return ret;
	/*
	 * TIMING TC REG20:
	 * - [0]:	Undocumented, but hardcoded init sequences
	 *		are always setting REG21/REG20 bit 0 to same value...
	 */
	return ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG20,
			      BIT(0), enable ? BIT(0) : 0);
}