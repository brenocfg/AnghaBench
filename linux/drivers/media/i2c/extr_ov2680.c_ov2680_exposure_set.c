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
typedef  int u32 ;
struct ov2680_ctrls {TYPE_1__* exposure; } ;
struct ov2680_dev {struct ov2680_ctrls ctrls; } ;
struct TYPE_2__ {scalar_t__ val; int /*<<< orphan*/  is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OV2680_REG_EXPOSURE_PK_HIGH ; 
 int /*<<< orphan*/  OV2680_REG_R_MANUAL ; 
 int ov2680_mod_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov2680_write_reg24 (struct ov2680_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov2680_exposure_set(struct ov2680_dev *sensor, bool auto_exp)
{
	struct ov2680_ctrls *ctrls = &sensor->ctrls;
	u32 exp;
	int ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_R_MANUAL, BIT(0),
			     auto_exp ? 0 : BIT(0));
	if (ret < 0)
		return ret;

	if (auto_exp || !ctrls->exposure->is_new)
		return 0;

	exp = (u32)ctrls->exposure->val;
	exp <<= 4;

	return ov2680_write_reg24(sensor, OV2680_REG_EXPOSURE_PK_HIGH, exp);
}