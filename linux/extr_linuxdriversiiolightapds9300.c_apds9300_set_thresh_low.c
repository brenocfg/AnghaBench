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
struct apds9300_data {int thresh_low; TYPE_1__* client; int /*<<< orphan*/  power_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int APDS9300_CMD ; 
 int APDS9300_THRESHLOWLOW ; 
 int APDS9300_THRESH_MAX ; 
 int APDS9300_WORD ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_word_data (TYPE_1__*,int,int) ; 

__attribute__((used)) static int apds9300_set_thresh_low(struct apds9300_data *data, int value)
{
	int ret;

	if (!data->power_state)
		return -EBUSY;

	if (value > APDS9300_THRESH_MAX)
		return -EINVAL;

	ret = i2c_smbus_write_word_data(data->client, APDS9300_THRESHLOWLOW
			| APDS9300_CMD | APDS9300_WORD, value);
	if (ret) {
		dev_err(&data->client->dev, "failed to set thresh_low\n");
		return ret;
	}
	data->thresh_low = value;

	return 0;
}