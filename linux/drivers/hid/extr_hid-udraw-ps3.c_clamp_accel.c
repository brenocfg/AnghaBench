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
struct TYPE_2__ {int min; int max; } ;

/* Variables and functions */
 TYPE_1__* accel_limits ; 
 int clamp (int,int,int) ; 

__attribute__((used)) static int clamp_accel(int axis, int offset)
{
	axis = clamp(axis,
			accel_limits[offset].min,
			accel_limits[offset].max);
	axis = (axis - accel_limits[offset].min) /
			((accel_limits[offset].max -
			  accel_limits[offset].min) * 0xFF);
	return axis;
}