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
struct jsa1212_data {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSA1212_ALS_DELAY_MS ; 
 int /*<<< orphan*/  JSA1212_ALS_DT1_REG ; 
 int /*<<< orphan*/  JSA1212_CONF_ALS_DISABLE ; 
 int /*<<< orphan*/  JSA1212_CONF_ALS_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int jsa1212_als_enable (struct jsa1212_data*,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int jsa1212_read_als_data(struct jsa1212_data *data,
				unsigned int *val)
{
	int ret;
	__le16 als_data;

	ret = jsa1212_als_enable(data, JSA1212_CONF_ALS_ENABLE);
	if (ret < 0)
		return ret;

	/* Delay for data output */
	msleep(JSA1212_ALS_DELAY_MS);

	/* Read 12 bit data */
	ret = regmap_bulk_read(data->regmap, JSA1212_ALS_DT1_REG, &als_data, 2);
	if (ret < 0) {
		dev_err(&data->client->dev, "als data read err\n");
		goto als_data_read_err;
	}

	*val = le16_to_cpu(als_data);

als_data_read_err:
	return jsa1212_als_enable(data, JSA1212_CONF_ALS_DISABLE);
}