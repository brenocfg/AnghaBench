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
struct v4l2_control {int member_1; int id; int /*<<< orphan*/  value; int /*<<< orphan*/  member_0; } ;
struct mt9m111 {int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct v4l2_control const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MT9M111_EFFECTS_MODE ; 
 int /*<<< orphan*/  MT9M111_EFFECTS_MODE_MASK ; 
#define  V4L2_COLORFX_BW 132 
#define  V4L2_COLORFX_NEGATIVE 131 
#define  V4L2_COLORFX_NONE 130 
#define  V4L2_COLORFX_SEPIA 129 
#define  V4L2_COLORFX_SOLARIZATION 128 
 int mt9m111_reg_mask (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_set_colorfx(struct mt9m111 *mt9m111, int val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	static const struct v4l2_control colorfx[] = {
		{ V4L2_COLORFX_NONE,		0 },
		{ V4L2_COLORFX_BW,		1 },
		{ V4L2_COLORFX_SEPIA,		2 },
		{ V4L2_COLORFX_NEGATIVE,	3 },
		{ V4L2_COLORFX_SOLARIZATION,	4 },
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(colorfx); i++) {
		if (colorfx[i].id == val) {
			return mt9m111_reg_mask(client, MT9M111_EFFECTS_MODE,
						colorfx[i].value,
						MT9M111_EFFECTS_MODE_MASK);
		}
	}

	return -EINVAL;
}