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
struct si2157_dev {int /*<<< orphan*/  ent; scalar_t__ mdev; int /*<<< orphan*/  stat_work; struct dvb_frontend* fe; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {int /*<<< orphan*/ * tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct si2157_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct si2157_dev*) ; 
 int /*<<< orphan*/  media_device_unregister_entity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si2157_remove(struct i2c_client *client)
{
	struct si2157_dev *dev = i2c_get_clientdata(client);
	struct dvb_frontend *fe = dev->fe;

	dev_dbg(&client->dev, "\n");

	/* stop statistics polling */
	cancel_delayed_work_sync(&dev->stat_work);

#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	if (dev->mdev)
		media_device_unregister_entity(&dev->ent);
#endif

	memset(&fe->ops.tuner_ops, 0, sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = NULL;
	kfree(dev);

	return 0;
}