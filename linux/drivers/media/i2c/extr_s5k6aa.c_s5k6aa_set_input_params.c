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
struct v4l2_rect {int width; int height; int left; int top; } ;
struct s5k6aa {scalar_t__ apply_crop; struct v4l2_rect ccd_rect; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_G_INPUTS_CHANGE_REQ ; 
 int /*<<< orphan*/  REG_G_PREVZOOM_IN_HEIGHT ; 
 int /*<<< orphan*/  REG_G_PREVZOOM_IN_WIDTH ; 
 int /*<<< orphan*/  REG_G_PREVZOOM_IN_XOFFS ; 
 int /*<<< orphan*/  REG_G_PREVZOOM_IN_YOFFS ; 
 int s5k6aa_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k6aa_set_input_params(struct s5k6aa *s5k6aa)
{
	struct i2c_client *c = v4l2_get_subdevdata(&s5k6aa->sd);
	struct v4l2_rect *r = &s5k6aa->ccd_rect;
	int ret;

	ret = s5k6aa_write(c, REG_G_PREVZOOM_IN_WIDTH, r->width);
	if (!ret)
		ret = s5k6aa_write(c, REG_G_PREVZOOM_IN_HEIGHT, r->height);
	if (!ret)
		ret = s5k6aa_write(c, REG_G_PREVZOOM_IN_XOFFS, r->left);
	if (!ret)
		ret = s5k6aa_write(c, REG_G_PREVZOOM_IN_YOFFS, r->top);
	if (!ret)
		ret = s5k6aa_write(c, REG_G_INPUTS_CHANGE_REQ, 1);
	if (!ret)
		s5k6aa->apply_crop = 0;

	return ret;
}