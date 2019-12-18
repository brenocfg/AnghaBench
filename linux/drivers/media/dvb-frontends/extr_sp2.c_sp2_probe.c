#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sp2_config {int /*<<< orphan*/  ci_control; int /*<<< orphan*/  priv; int /*<<< orphan*/  dvb_adap; } ;
struct sp2 {struct i2c_client* client; int /*<<< orphan*/  ci_control; int /*<<< orphan*/  priv; int /*<<< orphan*/  dvb_adap; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {struct sp2_config* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sp2*) ; 
 int /*<<< orphan*/  kfree (struct sp2*) ; 
 struct sp2* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sp2_init (struct sp2*) ; 

__attribute__((used)) static int sp2_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct sp2_config *cfg = client->dev.platform_data;
	struct sp2 *s;
	int ret;

	dev_dbg(&client->dev, "\n");

	s = kzalloc(sizeof(*s), GFP_KERNEL);
	if (!s) {
		ret = -ENOMEM;
		goto err;
	}

	s->client = client;
	s->dvb_adap = cfg->dvb_adap;
	s->priv = cfg->priv;
	s->ci_control = cfg->ci_control;

	i2c_set_clientdata(client, s);

	ret = sp2_init(s);
	if (ret)
		goto err;

	dev_info(&s->client->dev, "CIMaX SP2 successfully attached\n");
	return 0;
err:
	dev_dbg(&client->dev, "init failed=%d\n", ret);
	kfree(s);

	return ret;
}