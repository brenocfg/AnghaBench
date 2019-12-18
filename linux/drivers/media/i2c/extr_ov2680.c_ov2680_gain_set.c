#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ov2680_ctrls {TYPE_1__* gain; } ;
struct ov2680_dev {struct ov2680_ctrls ctrls; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  OV2680_REG_GAIN_PK ; 
 int /*<<< orphan*/  OV2680_REG_R_MANUAL ; 
 int ov2680_mod_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov2680_write_reg16 (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2680_gain_set(struct ov2680_dev *sensor, bool auto_gain)
{
	struct ov2680_ctrls *ctrls = &sensor->ctrls;
	u32 gain;
	int ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_R_MANUAL, BIT(1),
			     auto_gain ? 0 : BIT(1));
	if (ret < 0)
		return ret;

	if (auto_gain || !ctrls->gain->is_new)
		return 0;

	gain = ctrls->gain->val;

	ret = ov2680_write_reg16(sensor, OV2680_REG_GAIN_PK, gain);

	return 0;
}