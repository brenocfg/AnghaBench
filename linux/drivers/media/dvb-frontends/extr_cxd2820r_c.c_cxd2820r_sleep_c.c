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
struct reg_val_mask {int member_0; int member_1; int member_2; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {int /*<<< orphan*/  delivery_system; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct reg_val_mask*) ; 
 int /*<<< orphan*/  SYS_UNDEFINED ; 
 int cxd2820r_wr_reg_val_mask_tab (struct cxd2820r_priv*,struct reg_val_mask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

int cxd2820r_sleep_c(struct dvb_frontend *fe)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	int ret;
	struct reg_val_mask tab[] = {
		{ 0x000ff, 0x1f, 0xff },
		{ 0x00085, 0x00, 0xff },
		{ 0x00088, 0x01, 0xff },
		{ 0x00081, 0x00, 0xff },
		{ 0x00080, 0x00, 0xff },
	};

	dev_dbg(&client->dev, "\n");

	priv->delivery_system = SYS_UNDEFINED;

	ret = cxd2820r_wr_reg_val_mask_tab(priv, tab, ARRAY_SIZE(tab));
	if (ret)
		goto error;

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}