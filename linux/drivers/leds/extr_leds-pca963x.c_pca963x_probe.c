#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int num_leds; TYPE_1__* leds; } ;
struct pca963x_platform_data {scalar_t__ blink_type; scalar_t__ outdrv; scalar_t__ dir; TYPE_2__ leds; } ;
struct TYPE_9__ {int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  name; scalar_t__ default_trigger; } ;
struct pca963x_led {int led_num; TYPE_4__ led_cdev; struct pca963x* chip; int /*<<< orphan*/  name; } ;
struct pca963x_chipdef {int n_leds; scalar_t__ ledout_base; } ;
struct pca963x {struct i2c_client* client; struct pca963x_led* leds; struct pca963x_chipdef* chipdef; int /*<<< orphan*/  mutex; } ;
struct i2c_device_id {size_t driver_data; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_3__* adapter; } ;
struct TYPE_8__ {int nr; } ;
struct TYPE_6__ {char* name; scalar_t__ default_trigger; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pca963x_platform_data*) ; 
 scalar_t__ PCA963X_HW_BLINK ; 
 scalar_t__ PCA963X_INVERTED ; 
 scalar_t__ PCA963X_MODE1 ; 
 scalar_t__ PCA963X_MODE2 ; 
 scalar_t__ PCA963X_OPEN_DRAIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct pca963x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct pca963x_led* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct pca963x* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pca963x*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,scalar_t__,int) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pca963x_blink_set ; 
 struct pca963x_chipdef* pca963x_chipdefs ; 
 struct pca963x_platform_data* pca963x_get_pdata (struct i2c_client*,struct pca963x_chipdef*) ; 
 int /*<<< orphan*/  pca963x_led_set ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int pca963x_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct pca963x *pca963x_chip;
	struct pca963x_led *pca963x;
	struct pca963x_platform_data *pdata;
	struct pca963x_chipdef *chip;
	int i, err;

	chip = &pca963x_chipdefs[id->driver_data];
	pdata = dev_get_platdata(&client->dev);

	if (!pdata) {
		pdata = pca963x_get_pdata(client, chip);
		if (IS_ERR(pdata)) {
			dev_warn(&client->dev, "could not parse configuration\n");
			pdata = NULL;
		}
	}

	if (pdata && (pdata->leds.num_leds < 1 ||
				 pdata->leds.num_leds > chip->n_leds)) {
		dev_err(&client->dev, "board info must claim 1-%d LEDs",
								chip->n_leds);
		return -EINVAL;
	}

	pca963x_chip = devm_kzalloc(&client->dev, sizeof(*pca963x_chip),
								GFP_KERNEL);
	if (!pca963x_chip)
		return -ENOMEM;
	pca963x = devm_kcalloc(&client->dev, chip->n_leds, sizeof(*pca963x),
								GFP_KERNEL);
	if (!pca963x)
		return -ENOMEM;

	i2c_set_clientdata(client, pca963x_chip);

	mutex_init(&pca963x_chip->mutex);
	pca963x_chip->chipdef = chip;
	pca963x_chip->client = client;
	pca963x_chip->leds = pca963x;

	/* Turn off LEDs by default*/
	for (i = 0; i < chip->n_leds / 4; i++)
		i2c_smbus_write_byte_data(client, chip->ledout_base + i, 0x00);

	for (i = 0; i < chip->n_leds; i++) {
		pca963x[i].led_num = i;
		pca963x[i].chip = pca963x_chip;

		/* Platform data can specify LED names and default triggers */
		if (pdata && i < pdata->leds.num_leds) {
			if (pdata->leds.leds[i].name)
				snprintf(pca963x[i].name,
					 sizeof(pca963x[i].name), "pca963x:%s",
					 pdata->leds.leds[i].name);
			if (pdata->leds.leds[i].default_trigger)
				pca963x[i].led_cdev.default_trigger =
					pdata->leds.leds[i].default_trigger;
		}
		if (!pdata || i >= pdata->leds.num_leds ||
						!pdata->leds.leds[i].name)
			snprintf(pca963x[i].name, sizeof(pca963x[i].name),
				 "pca963x:%d:%.2x:%d", client->adapter->nr,
				 client->addr, i);

		pca963x[i].led_cdev.name = pca963x[i].name;
		pca963x[i].led_cdev.brightness_set_blocking = pca963x_led_set;

		if (pdata && pdata->blink_type == PCA963X_HW_BLINK)
			pca963x[i].led_cdev.blink_set = pca963x_blink_set;

		err = led_classdev_register(&client->dev, &pca963x[i].led_cdev);
		if (err < 0)
			goto exit;
	}

	/* Disable LED all-call address, and power down initially */
	i2c_smbus_write_byte_data(client, PCA963X_MODE1, BIT(4));

	if (pdata) {
		u8 mode2 = i2c_smbus_read_byte_data(pca963x->chip->client,
						    PCA963X_MODE2);
		/* Configure output: open-drain or totem pole (push-pull) */
		if (pdata->outdrv == PCA963X_OPEN_DRAIN)
			mode2 |= 0x01;
		else
			mode2 |= 0x05;
		/* Configure direction: normal or inverted */
		if (pdata->dir == PCA963X_INVERTED)
			mode2 |= 0x10;
		i2c_smbus_write_byte_data(pca963x->chip->client, PCA963X_MODE2,
					  mode2);
	}

	return 0;

exit:
	while (i--)
		led_classdev_unregister(&pca963x[i].led_cdev);

	return err;
}