#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_10__ {int /*<<< orphan*/  function; int /*<<< orphan*/  name; } ;
struct si2157_dev {scalar_t__ chiptype; int if_frequency; TYPE_2__ ent; TYPE_3__* pad; scalar_t__ mdev; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  if_port; int /*<<< orphan*/  inversion; struct dvb_frontend* fe; } ;
struct si2157_config {scalar_t__ mdev; int /*<<< orphan*/  if_port; int /*<<< orphan*/  inversion; struct dvb_frontend* fe; } ;
struct si2157_cmd {int rlen; scalar_t__ wlen; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_12__ {struct si2157_config* platform_data; } ;
struct i2c_client {TYPE_6__ dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {struct i2c_client* tuner_priv; TYPE_1__ ops; } ;
struct TYPE_11__ {void* sig_type; void* flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEDIA_ENT_F_TUNER ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 void* PAD_SIGNAL_ANALOG ; 
 void* PAD_SIGNAL_AUDIO ; 
 scalar_t__ SI2157_CHIPTYPE_SI2141 ; 
 scalar_t__ SI2157_CHIPTYPE_SI2146 ; 
 int /*<<< orphan*/  SI2157_NUM_PADS ; 
 size_t SI2157_PAD_AUD_OUT ; 
 size_t SI2157_PAD_RF_INPUT ; 
 size_t SI2157_PAD_VID_OUT ; 
 int /*<<< orphan*/  dev_dbg (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct si2157_dev*) ; 
 int /*<<< orphan*/  kfree (struct si2157_dev*) ; 
 struct si2157_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int media_device_register_entity (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_2__*) ; 
 int media_entity_pads_init (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int si2157_cmd_execute (struct i2c_client*,struct si2157_cmd*) ; 
 int /*<<< orphan*/  si2157_ops ; 
 int /*<<< orphan*/  si2157_stat_work ; 

__attribute__((used)) static int si2157_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct si2157_config *cfg = client->dev.platform_data;
	struct dvb_frontend *fe = cfg->fe;
	struct si2157_dev *dev;
	struct si2157_cmd cmd;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		goto err;
	}

	i2c_set_clientdata(client, dev);
	dev->fe = cfg->fe;
	dev->inversion = cfg->inversion;
	dev->if_port = cfg->if_port;
	dev->chiptype = (u8)id->driver_data;
	dev->if_frequency = 5000000; /* default value of property 0x0706 */
	mutex_init(&dev->i2c_mutex);
	INIT_DELAYED_WORK(&dev->stat_work, si2157_stat_work);

	/* check if the tuner is there */
	cmd.wlen = 0;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err_kfree;

	memcpy(&fe->ops.tuner_ops, &si2157_ops, sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = client;

#ifdef CONFIG_MEDIA_CONTROLLER
	if (cfg->mdev) {
		dev->mdev = cfg->mdev;

		dev->ent.name = KBUILD_MODNAME;
		dev->ent.function = MEDIA_ENT_F_TUNER;

		dev->pad[SI2157_PAD_RF_INPUT].flags = MEDIA_PAD_FL_SINK;
		dev->pad[SI2157_PAD_RF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
		dev->pad[SI2157_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
		dev->pad[SI2157_PAD_VID_OUT].sig_type = PAD_SIGNAL_ANALOG;
		dev->pad[SI2157_PAD_AUD_OUT].flags = MEDIA_PAD_FL_SOURCE;
		dev->pad[SI2157_PAD_AUD_OUT].sig_type = PAD_SIGNAL_AUDIO;

		ret = media_entity_pads_init(&dev->ent, SI2157_NUM_PADS,
					     &dev->pad[0]);

		if (ret)
			goto err_kfree;

		ret = media_device_register_entity(cfg->mdev, &dev->ent);
		if (ret) {
			media_entity_cleanup(&dev->ent);
			goto err_kfree;
		}
	}
#endif

	dev_info(&client->dev, "Silicon Labs %s successfully attached\n",
			dev->chiptype == SI2157_CHIPTYPE_SI2141 ?  "Si2141" :
			dev->chiptype == SI2157_CHIPTYPE_SI2146 ?
			"Si2146" : "Si2147/2148/2157/2158");

	return 0;

err_kfree:
	kfree(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}