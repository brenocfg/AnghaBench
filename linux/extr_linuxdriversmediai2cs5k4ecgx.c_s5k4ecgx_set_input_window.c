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
struct v4l2_rect {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_G_CAP_IN_HEIGHT ; 
 int /*<<< orphan*/  REG_G_CAP_IN_WIDTH ; 
 int /*<<< orphan*/  REG_G_CAP_IN_XOFFS ; 
 int /*<<< orphan*/  REG_G_CAP_IN_YOFFS ; 
 int /*<<< orphan*/  REG_G_PREV_IN_HEIGHT ; 
 int /*<<< orphan*/  REG_G_PREV_IN_WIDTH ; 
 int /*<<< orphan*/  REG_G_PREV_IN_XOFFS ; 
 int /*<<< orphan*/  REG_G_PREV_IN_YOFFS ; 
 int s5k4ecgx_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k4ecgx_set_input_window(struct i2c_client *c,
				     const struct v4l2_rect *r)
{
	int ret;

	ret = s5k4ecgx_write(c, REG_G_PREV_IN_WIDTH, r->width);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_PREV_IN_HEIGHT, r->height);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_PREV_IN_XOFFS, r->left);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_PREV_IN_YOFFS, r->top);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_CAP_IN_WIDTH, r->width);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_CAP_IN_HEIGHT, r->height);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_CAP_IN_XOFFS, r->left);
	if (!ret)
		ret = s5k4ecgx_write(c, REG_G_CAP_IN_YOFFS, r->top);

	return ret;
}