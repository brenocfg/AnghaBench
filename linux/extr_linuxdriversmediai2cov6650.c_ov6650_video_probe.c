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
typedef  scalar_t__ u8 ;
struct ov6650 {int /*<<< orphan*/  subdev; int /*<<< orphan*/  hdl; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OV6650_PIDH ; 
 scalar_t__ OV6650_PIDL ; 
 int /*<<< orphan*/  REG_MIDH ; 
 int /*<<< orphan*/  REG_MIDL ; 
 int /*<<< orphan*/  REG_PIDH ; 
 int /*<<< orphan*/  REG_PIDL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int ov6650_prog_dflt (struct i2c_client*) ; 
 int ov6650_reg_read (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ov6650_reset (struct i2c_client*) ; 
 int ov6650_s_power (int /*<<< orphan*/ *,int) ; 
 struct ov6650* to_ov6650 (struct i2c_client*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov6650_video_probe(struct i2c_client *client)
{
	struct ov6650 *priv = to_ov6650(client);
	u8		pidh, pidl, midh, midl;
	int		ret;

	ret = ov6650_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;

	/*
	 * check and show product ID and manufacturer ID
	 */
	ret = ov6650_reg_read(client, REG_PIDH, &pidh);
	if (!ret)
		ret = ov6650_reg_read(client, REG_PIDL, &pidl);
	if (!ret)
		ret = ov6650_reg_read(client, REG_MIDH, &midh);
	if (!ret)
		ret = ov6650_reg_read(client, REG_MIDL, &midl);

	if (ret)
		goto done;

	if ((pidh != OV6650_PIDH) || (pidl != OV6650_PIDL)) {
		dev_err(&client->dev, "Product ID error 0x%02x:0x%02x\n",
				pidh, pidl);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev,
		"ov6650 Product ID 0x%02x:0x%02x Manufacturer ID 0x%02x:0x%02x\n",
		pidh, pidl, midh, midl);

	ret = ov6650_reset(client);
	if (!ret)
		ret = ov6650_prog_dflt(client);
	if (!ret)
		ret = v4l2_ctrl_handler_setup(&priv->hdl);

done:
	ov6650_s_power(&priv->subdev, 0);
	return ret;
}