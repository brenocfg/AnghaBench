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
struct si1145_data {int meas_rate; TYPE_1__* part_info; } ;
struct TYPE_2__ {scalar_t__ uncompressed_meas_rate; } ;

/* Variables and functions */
 int IIO_VAL_FRACTIONAL ; 
 int si1145_uncompress (int) ; 

__attribute__((used)) static int si1145_read_samp_freq(struct si1145_data *data, int *val, int *val2)
{
	*val = 32000;
	if (data->part_info->uncompressed_meas_rate)
		*val2 = data->meas_rate;
	else
		*val2 = si1145_uncompress(data->meas_rate);
	return IIO_VAL_FRACTIONAL;
}