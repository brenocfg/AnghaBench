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
typedef  int /*<<< orphan*/  u8 ;
struct ov772x_priv {int /*<<< orphan*/  subdev; int /*<<< orphan*/  hdl; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MIDH ; 
 int /*<<< orphan*/  MIDL ; 
#define  OV7720 129 
#define  OV7725 128 
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  VER ; 
 int VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov772x_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int ov772x_s_power (int /*<<< orphan*/ *,int) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_video_probe(struct ov772x_priv *priv)
{
	struct i2c_client  *client = v4l2_get_subdevdata(&priv->subdev);
	u8                  pid, ver;
	const char         *devname;
	int		    ret;

	ret = ov772x_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;

	/*
	 * check and show product ID and manufacturer ID
	 */
	pid = ov772x_read(client, PID);
	ver = ov772x_read(client, VER);

	switch (VERSION(pid, ver)) {
	case OV7720:
		devname     = "ov7720";
		break;
	case OV7725:
		devname     = "ov7725";
		break;
	default:
		dev_err(&client->dev,
			"Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev,
		 "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname,
		 pid,
		 ver,
		 ov772x_read(client, MIDH),
		 ov772x_read(client, MIDL));
	ret = v4l2_ctrl_handler_setup(&priv->hdl);

done:
	ov772x_s_power(&priv->subdev, 0);
	return ret;
}