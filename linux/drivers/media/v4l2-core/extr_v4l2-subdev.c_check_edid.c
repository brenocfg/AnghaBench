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
struct v4l2_subdev_edid {int /*<<< orphan*/  pad; int /*<<< orphan*/ * edid; scalar_t__ blocks; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_pad (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_edid(struct v4l2_subdev *sd,
			     struct v4l2_subdev_edid *edid)
{
	if (!edid)
		return -EINVAL;

	if (edid->blocks && edid->edid == NULL)
		return -EINVAL;

	return check_pad(sd, edid->pad);
}