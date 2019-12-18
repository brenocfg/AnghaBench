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

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_INT_TIME ; 
 int** isl29501_int_time ; 
 int isl29501_register_write (struct isl29501_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isl29501_set_inttime(struct isl29501_private *isl29501,
				int val, int val2)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(isl29501_int_time); i++) {
		if (isl29501_int_time[i][0] == val &&
		    isl29501_int_time[i][1] == val2) {
			return isl29501_register_write(isl29501,
						       REG_INT_TIME,
						       i);
		}
	}

	return -EINVAL;
}