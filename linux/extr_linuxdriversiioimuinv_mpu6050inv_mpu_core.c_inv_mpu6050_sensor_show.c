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
struct inv_mpu6050_state {int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_MOD_X ; 
 int IIO_VAL_INT ; 
 scalar_t__ be16_to_cpup (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int inv_mpu6050_sensor_show(struct inv_mpu6050_state  *st, int reg,
				   int axis, int *val)
{
	int ind, result;
	__be16 d;

	ind = (axis - IIO_MOD_X) * 2;
	result = regmap_bulk_read(st->map, reg + ind, (u8 *)&d, 2);
	if (result)
		return -EINVAL;
	*val = (short)be16_to_cpup(&d);

	return IIO_VAL_INT;
}