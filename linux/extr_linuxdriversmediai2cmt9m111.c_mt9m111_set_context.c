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
struct mt9m111_context {int /*<<< orphan*/  control; } ;
struct mt9m111 {int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL ; 
 int reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_set_context(struct mt9m111 *mt9m111,
			       struct mt9m111_context *ctx)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	return reg_write(CONTEXT_CONTROL, ctx->control);
}