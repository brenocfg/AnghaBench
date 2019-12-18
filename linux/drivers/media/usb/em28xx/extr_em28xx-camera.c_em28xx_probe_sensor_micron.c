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
typedef  int u16 ;
struct i2c_client {int addr; } ;
struct em28xx {size_t def_i2c_bus; scalar_t__ em28xx_sensor; TYPE_1__* intf; struct i2c_client* i2c_client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EM28XX_MT9M001 ; 
 scalar_t__ EM28XX_MT9M111 ; 
 scalar_t__ EM28XX_MT9V011 ; 
 scalar_t__ EM28XX_NOSENSOR ; 
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ I2C_CLIENT_END ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int) ; 
 scalar_t__* micron_sensor_addrs ; 
 int swab16 (int) ; 

__attribute__((used)) static int em28xx_probe_sensor_micron(struct em28xx *dev)
{
	int ret, i;
	char *name;
	u16 id;

	struct i2c_client *client = &dev->i2c_client[dev->def_i2c_bus];

	dev->em28xx_sensor = EM28XX_NOSENSOR;
	for (i = 0; micron_sensor_addrs[i] != I2C_CLIENT_END; i++) {
		client->addr = micron_sensor_addrs[i];
		/* Read chip ID from register 0x00 */
		ret = i2c_smbus_read_word_data(client, 0x00); /* assumes LE */
		if (ret < 0) {
			if (ret != -ENXIO)
				dev_err(&dev->intf->dev,
					"couldn't read from i2c device 0x%02x: error %i\n",
				       client->addr << 1, ret);
			continue;
		}
		id = swab16(ret); /* LE -> BE */
		/* Read chip ID from register 0xff */
		ret = i2c_smbus_read_word_data(client, 0xff);
		if (ret < 0) {
			dev_err(&dev->intf->dev,
				"couldn't read from i2c device 0x%02x: error %i\n",
				client->addr << 1, ret);
			continue;
		}
		/* Validate chip ID to be sure we have a Micron device */
		if (id != swab16(ret))
			continue;
		/* Check chip ID */
		switch (id) {
		case 0x1222:
			name = "MT9V012"; /* MI370 */ /* 640x480 */
			break;
		case 0x1229:
			name = "MT9V112"; /* 640x480 */
			break;
		case 0x1433:
			name = "MT9M011"; /* 1280x1024 */
			break;
		case 0x143a:    /* found in the ECS G200 */
			name = "MT9M111"; /* MI1310 */ /* 1280x1024 */
			dev->em28xx_sensor = EM28XX_MT9M111;
			break;
		case 0x148c:
			name = "MT9M112"; /* MI1320 */ /* 1280x1024 */
			break;
		case 0x1511:
			name = "MT9D011"; /* MI2010 */ /* 1600x1200 */
			break;
		case 0x8232:
		case 0x8243:	/* rev B */
			name = "MT9V011"; /* MI360 */ /* 640x480 */
			dev->em28xx_sensor = EM28XX_MT9V011;
			break;
		case 0x8431:
			name = "MT9M001"; /* 1280x1024 */
			dev->em28xx_sensor = EM28XX_MT9M001;
			break;
		default:
			dev_info(&dev->intf->dev,
				 "unknown Micron sensor detected: 0x%04x\n",
				 id);
			return 0;
		}

		if (dev->em28xx_sensor == EM28XX_NOSENSOR)
			dev_info(&dev->intf->dev,
				 "unsupported sensor detected: %s\n", name);
		else
			dev_info(&dev->intf->dev,
				 "sensor %s detected\n", name);

		return 0;
	}

	return -ENODEV;
}