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
typedef  int /*<<< orphan*/  u16 ;
struct tda998x_priv {int /*<<< orphan*/  mutex; struct i2c_client* hdmi; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_WRITE_RANGE_BUF ; 
 int /*<<< orphan*/  REG2ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_page (struct tda998x_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reg_write_range(struct tda998x_priv *priv, u16 reg, u8 *p, int cnt)
{
	struct i2c_client *client = priv->hdmi;
	/* This is the maximum size of the buffer passed in */
	u8 buf[MAX_WRITE_RANGE_BUF + 1];
	int ret;

	if (cnt > MAX_WRITE_RANGE_BUF) {
		dev_err(&client->dev, "Fixed write buffer too small (%d)\n",
				MAX_WRITE_RANGE_BUF);
		return;
	}

	buf[0] = REG2ADDR(reg);
	memcpy(&buf[1], p, cnt);

	mutex_lock(&priv->mutex);
	ret = set_page(priv, reg);
	if (ret < 0)
		goto out;

	ret = i2c_master_send(client, buf, cnt + 1);
	if (ret < 0)
		dev_err(&client->dev, "Error %d writing to 0x%x\n", ret, reg);
out:
	mutex_unlock(&priv->mutex);
}