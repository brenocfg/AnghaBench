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
struct tw9910_priv {int revision; int /*<<< orphan*/  subdev; int /*<<< orphan*/ * scale; int /*<<< orphan*/  norm; TYPE_1__* info; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;
struct TYPE_2__ {int buswidth; } ;

/* Variables and functions */
 int ENODEV ; 
 int GET_ID (int) ; 
 int GET_REV (int) ; 
 int /*<<< orphan*/  ID ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int /*<<< orphan*/ * tw9910_ntsc_scales ; 
 int tw9910_s_power (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tw9910_video_probe(struct i2c_client *client)
{
	struct tw9910_priv *priv = to_tw9910(client);
	s32 id;
	int ret;

	/* TW9910 only use 8 or 16 bit bus width. */
	if (priv->info->buswidth != 16 && priv->info->buswidth != 8) {
		dev_err(&client->dev, "bus width error\n");
		return -ENODEV;
	}

	ret = tw9910_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;

	/*
	 * Check and show Product ID.
	 * So far only revisions 0 and 1 have been seen.
	 */
	id = i2c_smbus_read_byte_data(client, ID);
	priv->revision = GET_REV(id);
	id = GET_ID(id);

	if (id != 0x0b || priv->revision > 0x01) {
		dev_err(&client->dev, "Product ID error %x:%x\n",
			id, priv->revision);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev, "tw9910 Product ID %0x:%0x\n",
		 id, priv->revision);

	priv->norm = V4L2_STD_NTSC;
	priv->scale = &tw9910_ntsc_scales[0];

done:
	tw9910_s_power(&priv->subdev, 0);

	return ret;
}