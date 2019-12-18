#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mt9m111 {TYPE_2__* current_mode; TYPE_3__* ctx; int /*<<< orphan*/  hdl; TYPE_1__* fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  rect; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  read_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg_mask; int /*<<< orphan*/  reg_val; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt9m111_reg_mask (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_context (struct mt9m111*,TYPE_3__*) ; 
 int /*<<< orphan*/  mt9m111_set_pixfmt (struct mt9m111*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_setup_geometry (struct mt9m111*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt9m111_restore_state(struct mt9m111 *mt9m111)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);

	mt9m111_set_context(mt9m111, mt9m111->ctx);
	mt9m111_set_pixfmt(mt9m111, mt9m111->fmt->code);
	mt9m111_setup_geometry(mt9m111, &mt9m111->rect,
			mt9m111->width, mt9m111->height, mt9m111->fmt->code);
	v4l2_ctrl_handler_setup(&mt9m111->hdl);
	mt9m111_reg_mask(client, mt9m111->ctx->read_mode,
			 mt9m111->current_mode->reg_val,
			 mt9m111->current_mode->reg_mask);
}