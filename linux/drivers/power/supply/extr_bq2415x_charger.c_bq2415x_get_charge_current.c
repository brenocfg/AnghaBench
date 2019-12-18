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
struct TYPE_2__ {int resistor_sense; } ;
struct bq2415x_device {TYPE_1__ init_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_MASK_VI_CHRG ; 
 int /*<<< orphan*/  BQ2415X_REG_CURRENT ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_VI_CHRG ; 
 int EINVAL ; 
 int bq2415x_i2c_read_mask (struct bq2415x_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_get_charge_current(struct bq2415x_device *bq)
{
	int ret;

	if (bq->init_data.resistor_sense <= 0)
		return -EINVAL;

	ret = bq2415x_i2c_read_mask(bq, BQ2415X_REG_CURRENT,
			BQ2415X_MASK_VI_CHRG, BQ2415X_SHIFT_VI_CHRG);
	if (ret < 0)
		return ret;
	return (37400 + 6800*ret) / bq->init_data.resistor_sense;
}