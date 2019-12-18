#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct backlight_properties {void* max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {void* brightness; } ;
struct backlight_device {TYPE_2__ dev; TYPE_1__ props; } ;
struct adp8860_bl {int gdwn_dis; int en_ambl_sens; struct backlight_device* bl; int /*<<< orphan*/  revid; int /*<<< orphan*/  lock; scalar_t__ current_brightness; int /*<<< orphan*/  id; struct adp8860_backlight_platform_data* pdata; struct i2c_client* client; } ;
struct adp8860_backlight_platform_data {scalar_t__ num_leds; int /*<<< orphan*/  gdwn_dis; int /*<<< orphan*/  en_ambl_sens; } ;
typedef  int /*<<< orphan*/  props ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8860_DEVID (int /*<<< orphan*/ ) ; 
 int ADP8860_MANID (int /*<<< orphan*/ ) ; 
#define  ADP8860_MANUFID 130 
 void* ADP8860_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  ADP8860_MFDVID ; 
#define  ADP8861_MANUFID 129 
#define  ADP8863_MANUFID 128 
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  adp8860_bl_attr_group ; 
 int /*<<< orphan*/  adp8860_bl_ops ; 
 int adp8860_bl_setup (struct backlight_device*) ; 
 int /*<<< orphan*/  adp8860_led_probe (struct i2c_client*) ; 
 int adp8860_read (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct adp8860_backlight_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct adp8860_bl*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct adp8860_bl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adp8860_bl*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp8860_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct backlight_device *bl;
	struct adp8860_bl *data;
	struct adp8860_backlight_platform_data *pdata =
		dev_get_platdata(&client->dev);
	struct backlight_properties props;
	uint8_t reg_val;
	int ret;

	if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		return -EIO;
	}

	if (!pdata) {
		dev_err(&client->dev, "no platform data?\n");
		return -EINVAL;
	}

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	ret = adp8860_read(client, ADP8860_MFDVID, &reg_val);
	if (ret < 0)
		return ret;

	switch (ADP8860_MANID(reg_val)) {
	case ADP8863_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		/* fall through */
	case ADP8860_MANUFID:
		data->en_ambl_sens = !!pdata->en_ambl_sens;
		break;
	case ADP8861_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		break;
	default:
		dev_err(&client->dev, "failed to probe\n");
		return -ENODEV;
	}

	/* It's confirmed that the DEVID field is actually a REVID */

	data->revid = ADP8860_DEVID(reg_val);
	data->client = client;
	data->pdata = pdata;
	data->id = id->driver_data;
	data->current_brightness = 0;
	i2c_set_clientdata(client, data);

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = ADP8860_MAX_BRIGHTNESS;

	mutex_init(&data->lock);

	bl = devm_backlight_device_register(&client->dev,
				dev_driver_string(&client->dev),
				&client->dev, data, &adp8860_bl_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(&client->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}

	bl->props.brightness = ADP8860_MAX_BRIGHTNESS;

	data->bl = bl;

	if (data->en_ambl_sens)
		ret = sysfs_create_group(&bl->dev.kobj,
			&adp8860_bl_attr_group);

	if (ret) {
		dev_err(&client->dev, "failed to register sysfs\n");
		return ret;
	}

	ret = adp8860_bl_setup(bl);
	if (ret) {
		ret = -EIO;
		goto out;
	}

	backlight_update_status(bl);

	dev_info(&client->dev, "%s Rev.%d Backlight\n",
		client->name, data->revid);

	if (pdata->num_leds)
		adp8860_led_probe(client);

	return 0;

out:
	if (data->en_ambl_sens)
		sysfs_remove_group(&data->bl->dev.kobj,
			&adp8860_bl_attr_group);

	return ret;
}