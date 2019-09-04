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
struct mt9m111 {int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M111_TPG_CTRL ; 
 int /*<<< orphan*/  MT9M111_TPG_SEL_MASK ; 
 int mt9m111_reg_mask (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_set_test_pattern(struct mt9m111 *mt9m111, int val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);

	return mt9m111_reg_mask(client, MT9M111_TPG_CTRL, val,
				MT9M111_TPG_SEL_MASK);
}