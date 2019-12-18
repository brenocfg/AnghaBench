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
struct apds9300_data {TYPE_1__* client; int /*<<< orphan*/  power_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int APDS9300_CMD ; 
 int APDS9300_DATA0LOW ; 
 int APDS9300_DATA1LOW ; 
 int APDS9300_WORD ; 
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_word_data (TYPE_1__*,int) ; 

__attribute__((used)) static int apds9300_get_adc_val(struct apds9300_data *data, int adc_number)
{
	int ret;
	u8 flags = APDS9300_CMD | APDS9300_WORD;

	if (!data->power_state)
		return -EBUSY;

	/* Select ADC0 or ADC1 data register */
	flags |= adc_number ? APDS9300_DATA1LOW : APDS9300_DATA0LOW;

	ret = i2c_smbus_read_word_data(data->client, flags);
	if (ret < 0)
		dev_err(&data->client->dev,
			"failed to read ADC%d value\n", adc_number);

	return ret;
}