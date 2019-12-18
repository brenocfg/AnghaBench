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
struct hmc5843_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_CONFIG_REG_A ; 
 int /*<<< orphan*/  HMC5843_RATE_MASK ; 
 int HMC5843_RATE_OFFSET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hmc5843_set_samp_freq(struct hmc5843_data *data, u8 rate)
{
	int ret;

	mutex_lock(&data->lock);
	ret = regmap_update_bits(data->regmap, HMC5843_CONFIG_REG_A,
				 HMC5843_RATE_MASK,
				 rate << HMC5843_RATE_OFFSET);
	mutex_unlock(&data->lock);

	return ret;
}