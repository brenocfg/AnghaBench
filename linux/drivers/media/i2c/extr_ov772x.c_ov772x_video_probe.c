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
struct ov772x_priv {int /*<<< orphan*/  hdl; int /*<<< orphan*/  regmap; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MIDH ; 
 int /*<<< orphan*/  MIDL ; 
#define  OV7720 129 
#define  OV7725 128 
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  VER ; 
 int VERSION (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  ov772x_power_off (struct ov772x_priv*) ; 
 int ov772x_power_on (struct ov772x_priv*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_video_probe(struct ov772x_priv *priv)
{
	struct i2c_client  *client = v4l2_get_subdevdata(&priv->subdev);
	int		    pid, ver, midh, midl;
	const char         *devname;
	int		    ret;

	ret = ov772x_power_on(priv);
	if (ret < 0)
		return ret;

	/* Check and show product ID and manufacturer ID. */
	ret = regmap_read(priv->regmap, PID, &pid);
	if (ret < 0)
		return ret;
	ret = regmap_read(priv->regmap, VER, &ver);
	if (ret < 0)
		return ret;

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

	ret = regmap_read(priv->regmap, MIDH, &midh);
	if (ret < 0)
		return ret;
	ret = regmap_read(priv->regmap, MIDL, &midl);
	if (ret < 0)
		return ret;

	dev_info(&client->dev,
		 "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

	ret = v4l2_ctrl_handler_setup(&priv->hdl);

done:
	ov772x_power_off(priv);

	return ret;
}