#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_3__ entity; int /*<<< orphan*/  flags; } ;
struct mipid02_dev {int /*<<< orphan*/  lock; TYPE_1__ sd; int /*<<< orphan*/  notifier; TYPE_4__* pad; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  xclk; struct i2c_client* i2c_client; int /*<<< orphan*/  fmt; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_8__ {void* flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_VID_IF_BRIDGE ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  MIPID02_PAD_NB ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mipid02_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int mipid02_detect (struct mipid02_dev*) ; 
 int mipid02_get_regulators (struct mipid02_dev*) ; 
 int mipid02_parse_rx_ep (struct mipid02_dev*) ; 
 int mipid02_parse_tx_ep (struct mipid02_dev*) ; 
 int /*<<< orphan*/  mipid02_set_power_off (struct mipid02_dev*) ; 
 int mipid02_set_power_on (struct mipid02_dev*) ; 
 int /*<<< orphan*/  mipid02_subdev_entity_ops ; 
 int /*<<< orphan*/  mipid02_subdev_ops ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipid02_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct mipid02_dev *bridge;
	u32 clk_freq;
	int ret;

	bridge = devm_kzalloc(dev, sizeof(*bridge), GFP_KERNEL);
	if (!bridge)
		return -ENOMEM;

	init_format(&bridge->fmt);

	bridge->i2c_client = client;
	v4l2_i2c_subdev_init(&bridge->sd, client, &mipid02_subdev_ops);

	/* got and check clock */
	bridge->xclk = devm_clk_get(dev, "xclk");
	if (IS_ERR(bridge->xclk)) {
		dev_err(dev, "failed to get xclk\n");
		return PTR_ERR(bridge->xclk);
	}

	clk_freq = clk_get_rate(bridge->xclk);
	if (clk_freq < 6000000 || clk_freq > 27000000) {
		dev_err(dev, "xclk freq must be in 6-27 Mhz range. got %d Hz\n",
			clk_freq);
		return -EINVAL;
	}

	bridge->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);

	ret = mipid02_get_regulators(bridge);
	if (ret) {
		dev_err(dev, "failed to get regulators %d", ret);
		return ret;
	}

	mutex_init(&bridge->lock);
	bridge->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	bridge->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	bridge->sd.entity.ops = &mipid02_subdev_entity_ops;
	bridge->pad[0].flags = MEDIA_PAD_FL_SINK;
	bridge->pad[1].flags = MEDIA_PAD_FL_SINK;
	bridge->pad[2].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&bridge->sd.entity, MIPID02_PAD_NB,
				     bridge->pad);
	if (ret) {
		dev_err(&client->dev, "pads init failed %d", ret);
		goto mutex_cleanup;
	}

	/* enable clock, power and reset device if available */
	ret = mipid02_set_power_on(bridge);
	if (ret)
		goto entity_cleanup;

	ret = mipid02_detect(bridge);
	if (ret) {
		dev_err(&client->dev, "failed to detect mipid02 %d", ret);
		goto power_off;
	}

	ret = mipid02_parse_tx_ep(bridge);
	if (ret) {
		dev_err(&client->dev, "failed to parse tx %d", ret);
		goto power_off;
	}

	ret = mipid02_parse_rx_ep(bridge);
	if (ret) {
		dev_err(&client->dev, "failed to parse rx %d", ret);
		goto power_off;
	}

	ret = v4l2_async_register_subdev(&bridge->sd);
	if (ret < 0) {
		dev_err(&client->dev, "v4l2_async_register_subdev failed %d",
			    ret);
		goto unregister_notifier;
	}

	dev_info(&client->dev, "mipid02 device probe successfully");

	return 0;

unregister_notifier:
	v4l2_async_notifier_unregister(&bridge->notifier);
	v4l2_async_notifier_cleanup(&bridge->notifier);
power_off:
	mipid02_set_power_off(bridge);
entity_cleanup:
	media_entity_cleanup(&bridge->sd.entity);
mutex_cleanup:
	mutex_destroy(&bridge->lock);

	return ret;
}