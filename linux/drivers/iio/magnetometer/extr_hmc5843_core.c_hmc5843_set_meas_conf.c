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
typedef  int /*<<< orphan*/  u8 ;
struct hmc5843_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_CONFIG_REG_A ; 
 int /*<<< orphan*/  HMC5843_MEAS_CONF_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hmc5843_set_meas_conf(struct hmc5843_data *data, u8 meas_conf)
{
	int ret;

	mutex_lock(&data->lock);
	ret = regmap_update_bits(data->regmap, HMC5843_CONFIG_REG_A,
				 HMC5843_MEAS_CONF_MASK, meas_conf);
	mutex_unlock(&data->lock);

	return ret;
}