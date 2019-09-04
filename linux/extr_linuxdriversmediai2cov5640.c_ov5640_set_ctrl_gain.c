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
struct ov5640_ctrls {TYPE_2__* gain; TYPE_1__* auto_gain; } ;
struct ov5640_dev {struct ov5640_ctrls ctrls; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; scalar_t__ is_new; } ;
struct TYPE_3__ {scalar_t__ is_new; } ;

/* Variables and functions */
 int ov5640_set_autogain (struct ov5640_dev*,int) ; 
 int ov5640_set_gain (struct ov5640_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5640_set_ctrl_gain(struct ov5640_dev *sensor, bool auto_gain)
{
	struct ov5640_ctrls *ctrls = &sensor->ctrls;
	int ret = 0;

	if (ctrls->auto_gain->is_new) {
		ret = ov5640_set_autogain(sensor, auto_gain);
		if (ret)
			return ret;
	}

	if (!auto_gain && ctrls->gain->is_new)
		ret = ov5640_set_gain(sensor, ctrls->gain->val);

	return ret;
}