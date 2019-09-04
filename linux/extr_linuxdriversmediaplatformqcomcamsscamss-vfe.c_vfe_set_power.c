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
struct vfe_line {int dummy; } ;
struct vfe_device {TYPE_2__* camss; TYPE_1__* ops; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_version_read ) (struct vfe_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vfe_device*,int /*<<< orphan*/ ) ; 
 struct vfe_device* to_vfe (struct vfe_line*) ; 
 struct vfe_line* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int vfe_get (struct vfe_device*) ; 
 int /*<<< orphan*/  vfe_put (struct vfe_device*) ; 

__attribute__((used)) static int vfe_set_power(struct v4l2_subdev *sd, int on)
{
	struct vfe_line *line = v4l2_get_subdevdata(sd);
	struct vfe_device *vfe = to_vfe(line);
	int ret;

	if (on) {
		ret = vfe_get(vfe);
		if (ret < 0)
			return ret;

		vfe->ops->hw_version_read(vfe, vfe->camss->dev);
	} else {
		vfe_put(vfe);
	}

	return 0;
}