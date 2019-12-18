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
struct qt1050_priv {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT1050_CHIP_ID ; 
 unsigned int QT1050_CHIP_ID_VER ; 
 int /*<<< orphan*/  QT1050_FW_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static bool qt1050_identify(struct qt1050_priv *ts)
{
	unsigned int val;
	int err;

	/* Read Chip ID */
	regmap_read(ts->regmap, QT1050_CHIP_ID, &val);
	if (val != QT1050_CHIP_ID_VER) {
		dev_err(&ts->client->dev, "ID %d not supported\n", val);
		return false;
	}

	/* Read firmware version */
	err = regmap_read(ts->regmap, QT1050_FW_VERSION, &val);
	if (err) {
		dev_err(&ts->client->dev, "could not read the firmware version\n");
		return false;
	}

	dev_info(&ts->client->dev, "AT42QT1050 firmware version %1d.%1d\n",
		 val >> 4, val & 0xf);

	return true;
}