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
typedef  int /*<<< orphan*/  values ;
struct hmc5843_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_DATA_OUT_MSB_REGS ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int hmc5843_wait_measurement (struct hmc5843_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hmc5843_read_measurement(struct hmc5843_data *data,
				    int idx, int *val)
{
	__be16 values[3];
	int ret;

	mutex_lock(&data->lock);
	ret = hmc5843_wait_measurement(data);
	if (ret < 0) {
		mutex_unlock(&data->lock);
		return ret;
	}
	ret = regmap_bulk_read(data->regmap, HMC5843_DATA_OUT_MSB_REGS,
			       values, sizeof(values));
	mutex_unlock(&data->lock);
	if (ret < 0)
		return ret;

	*val = sign_extend32(be16_to_cpu(values[idx]), 15);
	return IIO_VAL_INT;
}