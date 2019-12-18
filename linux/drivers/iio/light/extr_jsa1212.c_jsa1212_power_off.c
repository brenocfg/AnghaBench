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
struct jsa1212_data {int /*<<< orphan*/  lock; TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int JSA1212_CONF_ALS_DISABLE ; 
 int JSA1212_CONF_ALS_MASK ; 
 int JSA1212_CONF_PXS_DISABLE ; 
 int JSA1212_CONF_PXS_MASK ; 
 int /*<<< orphan*/  JSA1212_CONF_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int jsa1212_power_off(struct jsa1212_data *data)
{
	int ret;

	mutex_lock(&data->lock);

	ret = regmap_update_bits(data->regmap, JSA1212_CONF_REG,
				JSA1212_CONF_ALS_MASK |
				JSA1212_CONF_PXS_MASK,
				JSA1212_CONF_ALS_DISABLE |
				JSA1212_CONF_PXS_DISABLE);

	if (ret < 0)
		dev_err(&data->client->dev, "power off cmd failed\n");

	mutex_unlock(&data->lock);

	return ret;
}