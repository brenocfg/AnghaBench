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
struct isl29501_private {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 scalar_t__ IIO_CURRENT ; 
 int /*<<< orphan*/  REG_DRIVER_RANGE ; 
 int** isl29501_current_scale_table ; 
 int isl29501_register_write (struct isl29501_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isl29501_set_scale(struct isl29501_private *isl29501,
			      const struct iio_chan_spec *chan,
			      int val, int val2)
{
	int i;

	if (chan->type != IIO_CURRENT)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(isl29501_current_scale_table); i++) {
		if (isl29501_current_scale_table[i][0] == val &&
		    isl29501_current_scale_table[i][1] == val2) {
			return isl29501_register_write(isl29501,
						       REG_DRIVER_RANGE,
						       i + 1);
		}
	}

	return -EINVAL;
}