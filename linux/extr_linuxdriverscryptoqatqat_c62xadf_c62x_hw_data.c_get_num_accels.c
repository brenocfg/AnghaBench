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
typedef  int u32 ;
struct adf_hw_device_data {int accel_mask; } ;

/* Variables and functions */
 int ADF_C62X_MAX_ACCELERATORS ; 

__attribute__((used)) static u32 get_num_accels(struct adf_hw_device_data *self)
{
	u32 i, ctr = 0;

	if (!self || !self->accel_mask)
		return 0;

	for (i = 0; i < ADF_C62X_MAX_ACCELERATORS; i++) {
		if (self->accel_mask & (1 << i))
			ctr++;
	}
	return ctr;
}