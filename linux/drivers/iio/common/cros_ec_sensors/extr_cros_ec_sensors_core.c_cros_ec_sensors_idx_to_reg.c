#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int sensor_num; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
struct cros_ec_sensors_core_state {scalar_t__ type; TYPE_2__ param; } ;

/* Variables and functions */
 int CROS_EC_SENSOR_MAX_AXIS ; 
 unsigned int EC_MEMMAP_ACC_DATA ; 
 unsigned int EC_MEMMAP_GYRO_DATA ; 
 scalar_t__ MOTIONSENSE_TYPE_ACCEL ; 

__attribute__((used)) static unsigned int cros_ec_sensors_idx_to_reg(
					struct cros_ec_sensors_core_state *st,
					unsigned int idx)
{
	/*
	 * When using LPC interface, only space for 2 Accel and one Gyro.
	 * First halfword of MOTIONSENSE_TYPE_ACCEL is used by angle.
	 */
	if (st->type == MOTIONSENSE_TYPE_ACCEL)
		return EC_MEMMAP_ACC_DATA + sizeof(u16) *
			(1 + idx + st->param.info.sensor_num *
			 CROS_EC_SENSOR_MAX_AXIS);

	return EC_MEMMAP_GYRO_DATA + sizeof(u16) * idx;
}