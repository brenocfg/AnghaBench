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
struct mt9t112_priv {int num_formats; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int) ; 
 int /*<<< orphan*/  mt9t112_cfmts ; 
 int /*<<< orphan*/  mt9t112_reg_read (int,struct i2c_client*,int) ; 
 int mt9t112_s_power (int /*<<< orphan*/ *,int) ; 
 struct mt9t112_priv* to_mt9t112 (struct i2c_client*) ; 

__attribute__((used)) static int mt9t112_camera_probe(struct i2c_client *client)
{
	struct mt9t112_priv *priv = to_mt9t112(client);
	const char          *devname;
	int                  chipid;
	int		     ret;

	ret = mt9t112_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;

	/* Check and show chip ID. */
	mt9t112_reg_read(chipid, client, 0x0000);

	switch (chipid) {
	case 0x2680:
		devname = "mt9t111";
		priv->num_formats = 1;
		break;
	case 0x2682:
		devname = "mt9t112";
		priv->num_formats = ARRAY_SIZE(mt9t112_cfmts);
		break;
	default:
		dev_err(&client->dev, "Product ID error %04x\n", chipid);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev, "%s chip ID %04x\n", devname, chipid);

done:
	mt9t112_s_power(&priv->subdev, 0);

	return ret;
}