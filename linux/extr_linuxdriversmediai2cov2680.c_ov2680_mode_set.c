#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ov2680_ctrls {TYPE_2__* auto_exp; TYPE_1__* auto_gain; } ;
struct ov2680_dev {int mode_pending_changes; int /*<<< orphan*/  current_mode; struct ov2680_ctrls ctrls; } ;
struct TYPE_4__ {scalar_t__ val; } ;
struct TYPE_3__ {scalar_t__ val; } ;

/* Variables and functions */
 scalar_t__ V4L2_EXPOSURE_AUTO ; 
 int ov2680_exposure_set (struct ov2680_dev*,int) ; 
 int ov2680_gain_set (struct ov2680_dev*,int) ; 
 int ov2680_load_regs (struct ov2680_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2680_mode_set(struct ov2680_dev *sensor)
{
	struct ov2680_ctrls *ctrls = &sensor->ctrls;
	int ret;

	ret = ov2680_gain_set(sensor, false);
	if (ret < 0)
		return ret;

	ret = ov2680_exposure_set(sensor, false);
	if (ret < 0)
		return ret;

	ret = ov2680_load_regs(sensor, sensor->current_mode);
	if (ret < 0)
		return ret;

	if (ctrls->auto_gain->val) {
		ret = ov2680_gain_set(sensor, true);
		if (ret < 0)
			return ret;
	}

	if (ctrls->auto_exp->val == V4L2_EXPOSURE_AUTO) {
		ret = ov2680_exposure_set(sensor, true);
		if (ret < 0)
			return ret;
	}

	sensor->mode_pending_changes = false;

	return 0;
}