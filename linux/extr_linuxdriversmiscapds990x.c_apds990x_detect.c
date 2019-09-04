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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct apds990x_chip {int revision; int /*<<< orphan*/  chipname; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_ID ; 
#define  APDS990X_ID_0 130 
#define  APDS990X_ID_29 129 
#define  APDS990X_ID_4 128 
 int /*<<< orphan*/  APDS990X_REV ; 
 int ENODEV ; 
 int apds990x_read_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int apds990x_detect(struct apds990x_chip *chip)
{
	struct i2c_client *client = chip->client;
	int ret;
	u8 id;

	ret = apds990x_read_byte(chip, APDS990X_ID, &id);
	if (ret < 0) {
		dev_err(&client->dev, "ID read failed\n");
		return ret;
	}

	ret = apds990x_read_byte(chip, APDS990X_REV, &chip->revision);
	if (ret < 0) {
		dev_err(&client->dev, "REV read failed\n");
		return ret;
	}

	switch (id) {
	case APDS990X_ID_0:
	case APDS990X_ID_4:
	case APDS990X_ID_29:
		snprintf(chip->chipname, sizeof(chip->chipname), "APDS-990x");
		break;
	default:
		ret = -ENODEV;
		break;
	}
	return ret;
}