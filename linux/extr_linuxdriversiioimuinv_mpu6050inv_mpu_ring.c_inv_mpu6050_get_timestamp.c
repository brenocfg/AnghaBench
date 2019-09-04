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
struct inv_mpu6050_state {int data_timestamp; int chip_period; } ;
typedef  int s64 ;

/* Variables and functions */
 int INV_MPU6050_FREQ_DIVIDER (struct inv_mpu6050_state*) ; 

__attribute__((used)) static s64 inv_mpu6050_get_timestamp(struct inv_mpu6050_state *st)
{
	s64 ts;

	/* return current data timestamp and increment */
	ts = st->data_timestamp;
	st->data_timestamp += st->chip_period * INV_MPU6050_FREQ_DIVIDER(st);

	return ts;
}