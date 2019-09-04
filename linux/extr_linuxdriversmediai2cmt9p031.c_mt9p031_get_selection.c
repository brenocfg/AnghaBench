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
struct v4l2_subdev_selection {scalar_t__ target; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; int /*<<< orphan*/  r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9p031 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/ * __mt9p031_get_pad_crop (struct mt9p031*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9p031* to_mt9p031 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9p031_get_selection(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_selection *sel)
{
	struct mt9p031 *mt9p031 = to_mt9p031(subdev);

	if (sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	sel->r = *__mt9p031_get_pad_crop(mt9p031, cfg, sel->pad, sel->which);
	return 0;
}