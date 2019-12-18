#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct v4l2_dv_timings {int dummy; } ;
struct TYPE_3__ {int reg_value; struct v4l2_dv_timings format; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ERANGE ; 
 int MASK_STD_STATUS ; 
 TYPE_1__* reg_fmt ; 

__attribute__((used)) static int gs_status_format(u16 status, struct v4l2_dv_timings *timings)
{
	int std = (status & MASK_STD_STATUS) >> 5;
	int i;

	for (i = 0; i < ARRAY_SIZE(reg_fmt); i++) {
		if (reg_fmt[i].reg_value == std) {
			*timings = reg_fmt[i].format;
			return 0;
		}
	}

	return -ERANGE;
}