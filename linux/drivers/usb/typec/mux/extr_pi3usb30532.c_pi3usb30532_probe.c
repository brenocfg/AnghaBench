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
struct typec_switch_desc {int /*<<< orphan*/  set; int /*<<< orphan*/  fwnode; struct pi3usb30532* drvdata; } ;
struct typec_mux_desc {int /*<<< orphan*/  set; int /*<<< orphan*/  fwnode; struct pi3usb30532* drvdata; } ;
struct pi3usb30532 {int conf; int /*<<< orphan*/  mux; int /*<<< orphan*/  sw; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct device {int /*<<< orphan*/  fwnode; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI3USB30532_CONF ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct pi3usb30532* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pi3usb30532*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi3usb30532_mux_set ; 
 int /*<<< orphan*/  pi3usb30532_sw_set ; 
 int /*<<< orphan*/  typec_mux_register (struct device*,struct typec_mux_desc*) ; 
 int /*<<< orphan*/  typec_switch_register (struct device*,struct typec_switch_desc*) ; 
 int /*<<< orphan*/  typec_switch_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pi3usb30532_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct typec_switch_desc sw_desc;
	struct typec_mux_desc mux_desc;
	struct pi3usb30532 *pi;
	int ret;

	pi = devm_kzalloc(dev, sizeof(*pi), GFP_KERNEL);
	if (!pi)
		return -ENOMEM;

	pi->client = client;
	mutex_init(&pi->lock);

	ret = i2c_smbus_read_byte_data(client, PI3USB30532_CONF);
	if (ret < 0) {
		dev_err(dev, "Error reading config register %d\n", ret);
		return ret;
	}
	pi->conf = ret;

	sw_desc.drvdata = pi;
	sw_desc.fwnode = dev->fwnode;
	sw_desc.set = pi3usb30532_sw_set;

	pi->sw = typec_switch_register(dev, &sw_desc);
	if (IS_ERR(pi->sw)) {
		dev_err(dev, "Error registering typec switch: %ld\n",
			PTR_ERR(pi->sw));
		return PTR_ERR(pi->sw);
	}

	mux_desc.drvdata = pi;
	mux_desc.fwnode = dev->fwnode;
	mux_desc.set = pi3usb30532_mux_set;

	pi->mux = typec_mux_register(dev, &mux_desc);
	if (IS_ERR(pi->mux)) {
		typec_switch_unregister(pi->sw);
		dev_err(dev, "Error registering typec mux: %ld\n",
			PTR_ERR(pi->mux));
		return PTR_ERR(pi->mux);
	}

	i2c_set_clientdata(client, pi);
	return 0;
}