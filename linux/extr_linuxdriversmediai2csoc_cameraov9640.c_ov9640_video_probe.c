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
struct v4l2_subdev {int dummy; } ;
struct ov9640_priv {int revision; int /*<<< orphan*/  subdev; int /*<<< orphan*/  hdl; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OV9640_MIDH ; 
 int /*<<< orphan*/  OV9640_MIDL ; 
 int /*<<< orphan*/  OV9640_PID ; 
#define  OV9640_V2 129 
#define  OV9640_V3 128 
 int /*<<< orphan*/  OV9640_VER ; 
 int VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int ov9640_reg_read (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ov9640_s_power (int /*<<< orphan*/ *,int) ; 
 struct ov9640_priv* to_ov9640_sensor (struct v4l2_subdev*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov9640_video_probe(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct ov9640_priv *priv = to_ov9640_sensor(sd);
	u8		pid, ver, midh, midl;
	const char	*devname;
	int		ret;

	ret = ov9640_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;

	/*
	 * check and show product ID and manufacturer ID
	 */

	ret = ov9640_reg_read(client, OV9640_PID, &pid);
	if (!ret)
		ret = ov9640_reg_read(client, OV9640_VER, &ver);
	if (!ret)
		ret = ov9640_reg_read(client, OV9640_MIDH, &midh);
	if (!ret)
		ret = ov9640_reg_read(client, OV9640_MIDL, &midl);
	if (ret)
		goto done;

	switch (VERSION(pid, ver)) {
	case OV9640_V2:
		devname		= "ov9640";
		priv->revision	= 2;
		break;
	case OV9640_V3:
		devname		= "ov9640";
		priv->revision	= 3;
		break;
	default:
		dev_err(&client->dev, "Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev, "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

	ret = v4l2_ctrl_handler_setup(&priv->hdl);

done:
	ov9640_s_power(&priv->subdev, 0);
	return ret;
}