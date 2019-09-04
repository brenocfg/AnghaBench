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
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {size_t res_type; int /*<<< orphan*/  lock; TYPE_1__* ffmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M5MOLS_RESTYPE_CAPTURE ; 
 int /*<<< orphan*/  M5MOLS_RESTYPE_MONITOR ; 
 int /*<<< orphan*/  REG_PARAMETER ; 
 scalar_t__ is_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int m5mols_set_mode (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int m5mols_start_capture (struct m5mols_info*) ; 
 int m5mols_start_monitor (struct m5mols_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 

__attribute__((used)) static int m5mols_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct m5mols_info *info = to_m5mols(sd);
	u32 code;
	int ret;

	mutex_lock(&info->lock);
	code = info->ffmt[info->res_type].code;

	if (enable) {
		if (is_code(code, M5MOLS_RESTYPE_MONITOR))
			ret = m5mols_start_monitor(info);
		else if (is_code(code, M5MOLS_RESTYPE_CAPTURE))
			ret = m5mols_start_capture(info);
		else
			ret = -EINVAL;
	} else {
		ret = m5mols_set_mode(info, REG_PARAMETER);
	}

	mutex_unlock(&info->lock);
	return ret;
}