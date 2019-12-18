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
struct v4l2_subdev {int dummy; } ;
struct mt9m001_reg {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct mt9m001 {scalar_t__ y_skip_top; TYPE_1__ rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct mt9m001_reg const*) ; 
 int /*<<< orphan*/  MT9M001_COLUMN_START ; 
 int /*<<< orphan*/  MT9M001_DEFAULT_HBLANK ; 
 int /*<<< orphan*/  MT9M001_DEFAULT_VBLANK ; 
 int /*<<< orphan*/  MT9M001_HORIZONTAL_BLANKING ; 
 int /*<<< orphan*/  MT9M001_ROW_START ; 
 int /*<<< orphan*/  MT9M001_VERTICAL_BLANKING ; 
 int /*<<< orphan*/  MT9M001_WINDOW_HEIGHT ; 
 int /*<<< orphan*/  MT9M001_WINDOW_WIDTH ; 
 int multi_reg_write (struct i2c_client*,struct mt9m001_reg const*,int /*<<< orphan*/ ) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m001_apply_selection(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	const struct mt9m001_reg regs[] = {
		/* Blanking and start values - default... */
		{ MT9M001_HORIZONTAL_BLANKING, MT9M001_DEFAULT_HBLANK },
		{ MT9M001_VERTICAL_BLANKING, MT9M001_DEFAULT_VBLANK },
		/*
		 * The caller provides a supported format, as verified per
		 * call to .set_fmt(FORMAT_TRY).
		 */
		{ MT9M001_COLUMN_START, mt9m001->rect.left },
		{ MT9M001_ROW_START, mt9m001->rect.top },
		{ MT9M001_WINDOW_WIDTH, mt9m001->rect.width - 1 },
		{ MT9M001_WINDOW_HEIGHT,
			mt9m001->rect.height + mt9m001->y_skip_top - 1 },
	};

	return multi_reg_write(client, regs, ARRAY_SIZE(regs));
}