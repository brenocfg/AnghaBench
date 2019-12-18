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
struct mt9m111 {TYPE_1__* ctx; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_mode; } ;

/* Variables and functions */
 int mt9m111_reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int mt9m111_reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_set_flip(struct mt9m111 *mt9m111, int flip, int mask)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	int ret;

	if (flip)
		ret = mt9m111_reg_set(client, mt9m111->ctx->read_mode, mask);
	else
		ret = mt9m111_reg_clear(client, mt9m111->ctx->read_mode, mask);

	return ret;
}