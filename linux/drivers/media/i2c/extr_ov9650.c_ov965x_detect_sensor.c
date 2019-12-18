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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct ov965x {scalar_t__ id; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OV9650_ID ; 
 scalar_t__ OV9652_ID ; 
 scalar_t__ OV965X_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_PID ; 
 int /*<<< orphan*/  REG_VER ; 
 int __ov965x_set_power (struct ov965x*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov965x_read (struct ov965x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ov965x* to_ov965x (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,scalar_t__) ; 

__attribute__((used)) static int ov965x_detect_sensor(struct v4l2_subdev *sd)
{
	struct ov965x *ov965x = to_ov965x(sd);
	u8 pid, ver;
	int ret;

	mutex_lock(&ov965x->lock);
	ret = __ov965x_set_power(ov965x, 1);
	if (ret)
		goto out;

	msleep(25);

	/* Check sensor revision */
	ret = ov965x_read(ov965x, REG_PID, &pid);
	if (!ret)
		ret = ov965x_read(ov965x, REG_VER, &ver);

	__ov965x_set_power(ov965x, 0);

	if (!ret) {
		ov965x->id = OV965X_ID(pid, ver);
		if (ov965x->id == OV9650_ID || ov965x->id == OV9652_ID) {
			v4l2_info(sd, "Found OV%04X sensor\n", ov965x->id);
		} else {
			v4l2_err(sd, "Sensor detection failed (%04X, %d)\n",
				 ov965x->id, ret);
			ret = -ENODEV;
		}
	}
out:
	mutex_unlock(&ov965x->lock);

	return ret;
}