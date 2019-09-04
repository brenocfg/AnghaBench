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
struct v4l2_rect {int width; int height; int left; int top; } ;
struct v4l2_subdev_selection {scalar_t__ which; scalar_t__ target; struct v4l2_rect r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int left; int width; int top; int height; } ;
struct ov6650 {TYPE_1__ rect; } ;
struct i2c_client {int dummy; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int DEF_HSTRT ; 
 int DEF_VSTRT ; 
 int EINVAL ; 
 scalar_t__ H_CIF ; 
 int /*<<< orphan*/  REG_HSTOP ; 
 int /*<<< orphan*/  REG_HSTRT ; 
 int /*<<< orphan*/  REG_VSTOP ; 
 int /*<<< orphan*/  REG_VSTRT ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 scalar_t__ W_CIF ; 
 int ov6650_reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct ov6650* to_ov6650 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int*,int,scalar_t__,int,int*,int,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov6650_set_selection(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_selection *sel)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov6650 *priv = to_ov6650(client);
	struct v4l2_rect rect = sel->r;
	int ret;

	if (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	v4l_bound_align_image(&rect.width, 2, W_CIF, 1,
			      &rect.height, 2, H_CIF, 1, 0);
	v4l_bound_align_image(&rect.left, DEF_HSTRT << 1,
			      (DEF_HSTRT << 1) + W_CIF - (__s32)rect.width, 1,
			      &rect.top, DEF_VSTRT << 1,
			      (DEF_VSTRT << 1) + H_CIF - (__s32)rect.height, 1,
			      0);

	ret = ov6650_reg_write(client, REG_HSTRT, rect.left >> 1);
	if (!ret) {
		priv->rect.left = rect.left;
		ret = ov6650_reg_write(client, REG_HSTOP,
				(rect.left + rect.width) >> 1);
	}
	if (!ret) {
		priv->rect.width = rect.width;
		ret = ov6650_reg_write(client, REG_VSTRT, rect.top >> 1);
	}
	if (!ret) {
		priv->rect.top = rect.top;
		ret = ov6650_reg_write(client, REG_VSTOP,
				(rect.top + rect.height) >> 1);
	}
	if (!ret)
		priv->rect.height = rect.height;

	return ret;
}