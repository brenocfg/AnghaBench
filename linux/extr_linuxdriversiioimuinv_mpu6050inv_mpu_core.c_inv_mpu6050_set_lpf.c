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
struct TYPE_2__ {int lpf; } ;
struct inv_mpu6050_state {TYPE_1__ chip_config; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
#define  INV_MPU6050_FILTER_10HZ 133 
#define  INV_MPU6050_FILTER_188HZ 132 
#define  INV_MPU6050_FILTER_20HZ 131 
#define  INV_MPU6050_FILTER_42HZ 130 
#define  INV_MPU6050_FILTER_5HZ 129 
#define  INV_MPU6050_FILTER_98HZ 128 
 int inv_mpu6050_set_lpf_regs (struct inv_mpu6050_state*,int) ; 

__attribute__((used)) static int inv_mpu6050_set_lpf(struct inv_mpu6050_state *st, int rate)
{
	static const int hz[] = {188, 98, 42, 20, 10, 5};
	static const int d[] = {
		INV_MPU6050_FILTER_188HZ, INV_MPU6050_FILTER_98HZ,
		INV_MPU6050_FILTER_42HZ, INV_MPU6050_FILTER_20HZ,
		INV_MPU6050_FILTER_10HZ, INV_MPU6050_FILTER_5HZ
	};
	int i, h, result;
	u8 data;

	h = (rate >> 1);
	i = 0;
	while ((h < hz[i]) && (i < ARRAY_SIZE(d) - 1))
		i++;
	data = d[i];
	result = inv_mpu6050_set_lpf_regs(st, data);
	if (result)
		return result;
	st->chip_config.lpf = data;

	return 0;
}