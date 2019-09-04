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
typedef  size_t u32 ;
struct isl29501_private {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  REG_INT_TIME ; 
 int** isl29501_int_time ; 
 int isl29501_register_read (struct isl29501_private*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int isl29501_get_inttime(struct isl29501_private *isl29501,
				int *val, int *val2)
{
	int ret;
	u32 inttime;

	ret = isl29501_register_read(isl29501, REG_INT_TIME, &inttime);
	if (ret < 0)
		return ret;

	if (inttime >= ARRAY_SIZE(isl29501_int_time))
		return -EINVAL;

	*val = isl29501_int_time[inttime][0];
	*val2 = isl29501_int_time[inttime][1];

	return IIO_VAL_INT_PLUS_MICRO;
}