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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct venc_state {struct v4l2_subdev sd; } ;
struct v4l2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct venc_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ v4l2_device_register_subdev (struct v4l2_device*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_device*,char*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venc_device_get ; 
 scalar_t__ venc_initialize (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  venc_ops ; 

struct v4l2_subdev *venc_sub_dev_init(struct v4l2_device *v4l2_dev,
		const char *venc_name)
{
	struct venc_state *venc = NULL;

	bus_for_each_dev(&platform_bus_type, NULL, &venc,
			venc_device_get);
	if (venc == NULL)
		return NULL;

	v4l2_subdev_init(&venc->sd, &venc_ops);

	strscpy(venc->sd.name, venc_name, sizeof(venc->sd.name));
	if (v4l2_device_register_subdev(v4l2_dev, &venc->sd) < 0) {
		v4l2_err(v4l2_dev,
			"vpbe unable to register venc sub device\n");
		return NULL;
	}
	if (venc_initialize(&venc->sd)) {
		v4l2_err(v4l2_dev,
			"vpbe venc initialization failed\n");
		return NULL;
	}

	return &venc->sd;
}