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
struct tda18250_dev {struct dvb_frontend* fe; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {int /*<<< orphan*/ * tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct tda18250_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tda18250_dev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tda18250_remove(struct i2c_client *client)
{
	struct tda18250_dev *dev = i2c_get_clientdata(client);
	struct dvb_frontend *fe = dev->fe;

	dev_dbg(&client->dev, "\n");

	memset(&fe->ops.tuner_ops, 0, sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = NULL;
	kfree(dev);

	return 0;
}