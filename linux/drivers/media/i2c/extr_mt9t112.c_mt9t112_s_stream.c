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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9t112_priv {int init_done; TYPE_3__ frame; TYPE_2__* format; TYPE_1__* info; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int fmt; int order; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_INFO (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECHECKER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_CLOCK ; 
 int MT9T112_FLAG_PCLK_RISING_EDGE ; 
 int /*<<< orphan*/  VAR (int,int) ; 
 int /*<<< orphan*/  VAR8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGA_HEIGHT ; 
 int /*<<< orphan*/  VGA_WIDTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mt9t112_auto_focus_trigger (struct i2c_client*) ; 
 int /*<<< orphan*/  mt9t112_init_camera (struct i2c_client*) ; 
 int /*<<< orphan*/  mt9t112_mcu_write (int,struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt9t112_reg_write (int,struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  mt9t112_set_a_frame_size (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9t112_priv* to_mt9t112 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t112_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t112_priv *priv = to_mt9t112(client);
	int ret = 0;

	if (!enable) {
		/* FIXME
		 *
		 * If user selected large output size, and used it long time,
		 * mt9t112 camera will be very warm.
		 *
		 * But current driver can not stop mt9t112 camera.
		 * So, set small size here to solve this problem.
		 */
		mt9t112_set_a_frame_size(client, VGA_WIDTH, VGA_HEIGHT);
		return ret;
	}

	if (!priv->init_done) {
		u16 param = MT9T112_FLAG_PCLK_RISING_EDGE & priv->info->flags ?
			    0x0001 : 0x0000;

		ECHECKER(ret, mt9t112_init_camera(client));

		/* Invert PCLK (Data sampled on falling edge of pixclk). */
		mt9t112_reg_write(ret, client, 0x3C20, param);

		mdelay(5);

		priv->init_done = true;
	}

	mt9t112_mcu_write(ret, client, VAR(26, 7), priv->format->fmt);
	mt9t112_mcu_write(ret, client, VAR(26, 9), priv->format->order);
	mt9t112_mcu_write(ret, client, VAR8(1, 0), 0x06);

	mt9t112_set_a_frame_size(client, priv->frame.width, priv->frame.height);

	ECHECKER(ret, mt9t112_auto_focus_trigger(client));

	dev_dbg(&client->dev, "format : %d\n", priv->format->code);
	dev_dbg(&client->dev, "size   : %d x %d\n",
		priv->frame.width,
		priv->frame.height);

	CLOCK_INFO(client, EXT_CLOCK);

	return ret;
}