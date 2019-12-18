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
struct vfe_line {int dummy; } ;
struct vfe_device {TYPE_1__* camss; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct vfe_device* to_vfe (struct vfe_line*) ; 
 struct vfe_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int vfe_disable (struct vfe_line*) ; 
 int vfe_enable (struct vfe_line*) ; 

__attribute__((used)) static int vfe_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct vfe_line *line = v4l2_get_subdevdata(sd);
	struct vfe_device *vfe = to_vfe(line);
	int ret;

	if (enable) {
		ret = vfe_enable(line);
		if (ret < 0)
			dev_err(vfe->camss->dev,
				"Failed to enable vfe outputs\n");
	} else {
		ret = vfe_disable(line);
		if (ret < 0)
			dev_err(vfe->camss->dev,
				"Failed to disable vfe outputs\n");
	}

	return ret;
}