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
typedef  int u8 ;
struct ltr501_data {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LTR501_ALS_PS_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ltr501_drdy(struct ltr501_data *data, u8 drdy_mask)
{
	int tries = 100;
	int ret, status;

	while (tries--) {
		ret = regmap_read(data->regmap, LTR501_ALS_PS_STATUS, &status);
		if (ret < 0)
			return ret;
		if ((status & drdy_mask) == drdy_mask)
			return 0;
		msleep(25);
	}

	dev_err(&data->client->dev, "ltr501_drdy() failed, data not ready\n");
	return -EIO;
}