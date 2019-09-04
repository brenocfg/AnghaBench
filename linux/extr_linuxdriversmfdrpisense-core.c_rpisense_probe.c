#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rpisense_js {int /*<<< orphan*/  pdev; int /*<<< orphan*/ * keys_desc; } ;
struct rpisense {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_8__ {TYPE_1__ framebuffer; struct rpisense_js joystick; int /*<<< orphan*/ * dev; struct i2c_client* i2c_client; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPISENSE_VER ; 
 int /*<<< orphan*/  RPISENSE_WAI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpio_to_desc (int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,TYPE_2__*) ; 
 TYPE_2__* rpisense ; 
 int /*<<< orphan*/  rpisense_client_dev_register (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int rpisense_reg_read (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpisense_probe(struct i2c_client *i2c,
			       const struct i2c_device_id *id)
{
	int ret;
	struct rpisense_js *rpisense_js;

	rpisense = devm_kzalloc(&i2c->dev, sizeof(struct rpisense), GFP_KERNEL);
	if (rpisense == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rpisense);
	rpisense->dev = &i2c->dev;
	rpisense->i2c_client = i2c;

	ret = rpisense_reg_read(rpisense, RPISENSE_WAI);
	if (ret > 0) {
		if (ret != 's')
			return -EINVAL;
	} else {
		return ret;
	}
	ret = rpisense_reg_read(rpisense, RPISENSE_VER);
	if (ret < 0)
		return ret;

	dev_info(rpisense->dev,
		 "Raspberry Pi Sense HAT firmware version %i\n", ret);

	rpisense_js = &rpisense->joystick;
	rpisense_js->keys_desc = devm_gpiod_get(&i2c->dev,
						"keys-int", GPIOD_IN);
	if (IS_ERR(rpisense_js->keys_desc)) {
		dev_warn(&i2c->dev, "Failed to get keys-int descriptor.\n");
		rpisense_js->keys_desc = gpio_to_desc(23);
		if (rpisense_js->keys_desc == NULL) {
			dev_err(&i2c->dev, "GPIO23 fallback failed.\n");
			return PTR_ERR(rpisense_js->keys_desc);
		}
	}
	rpisense_client_dev_register(rpisense, "rpi-sense-js",
				     &(rpisense->joystick.pdev));
	rpisense_client_dev_register(rpisense, "rpi-sense-fb",
				     &(rpisense->framebuffer.pdev));

	return 0;
}