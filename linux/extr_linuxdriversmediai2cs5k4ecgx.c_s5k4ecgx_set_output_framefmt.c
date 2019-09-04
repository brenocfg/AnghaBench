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
struct s5k4ecgx {TYPE_1__* curr_pixfmt; TYPE_3__* curr_frmsize; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {TYPE_2__ size; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_p_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_P_FMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P_OUT_HEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P_OUT_WIDTH (int /*<<< orphan*/ ) ; 
 int s5k4ecgx_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k4ecgx_set_output_framefmt(struct s5k4ecgx *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	int ret;

	ret = s5k4ecgx_write(client, REG_P_OUT_WIDTH(0),
			     priv->curr_frmsize->size.width);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_OUT_HEIGHT(0),
				     priv->curr_frmsize->size.height);
	if (!ret)
		ret = s5k4ecgx_write(client, REG_P_FMT(0),
				     priv->curr_pixfmt->reg_p_format);
	return ret;
}