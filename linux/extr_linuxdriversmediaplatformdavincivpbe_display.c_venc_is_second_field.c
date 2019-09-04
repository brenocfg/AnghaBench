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
struct vpbe_display {struct vpbe_device* vpbe_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  venc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENC_GET_FLD ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int venc_is_second_field(struct vpbe_display *disp_dev)
{
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	int ret, val;

	ret = v4l2_subdev_call(vpbe_dev->venc,
			       core,
			       ioctl,
			       VENC_GET_FLD,
			       &val);
	if (ret < 0) {
		v4l2_err(&vpbe_dev->v4l2_dev,
			 "Error in getting Field ID 0\n");
		return 1;
	}
	return val;
}