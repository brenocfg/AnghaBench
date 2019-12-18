#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {struct a8293_platform_data* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  set_voltage; } ;
struct dvb_frontend {struct a8293_dev* sec_priv; TYPE_1__ ops; } ;
struct a8293_platform_data {struct dvb_frontend* dvb_frontend; } ;
struct a8293_dev {struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  a8293_set_voltage ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct a8293_dev*) ; 
 int /*<<< orphan*/  kfree (struct a8293_dev*) ; 
 struct a8293_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a8293_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct a8293_dev *dev;
	struct a8293_platform_data *pdata = client->dev.platform_data;
	struct dvb_frontend *fe = pdata->dvb_frontend;
	int ret;
	u8 buf[2];

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	dev->client = client;

	/* check if the SEC is there */
	ret = i2c_master_recv(client, buf, 2);
	if (ret < 0)
		goto err_kfree;

	/* override frontend ops */
	fe->ops.set_voltage = a8293_set_voltage;
	fe->sec_priv = dev;
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "Allegro A8293 SEC successfully attached\n");
	return 0;
err_kfree:
	kfree(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}