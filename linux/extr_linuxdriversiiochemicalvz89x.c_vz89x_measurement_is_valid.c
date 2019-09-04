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
struct vz89x_data {scalar_t__* buffer; TYPE_1__* chip; } ;
struct TYPE_2__ {int read_size; } ;

/* Variables and functions */
 size_t VZ89X_VOC_SHORT_IDX ; 

__attribute__((used)) static bool vz89x_measurement_is_valid(struct vz89x_data *data)
{
	if (data->buffer[VZ89X_VOC_SHORT_IDX] == 0)
		return true;

	return !!(data->buffer[data->chip->read_size - 1] > 0);
}