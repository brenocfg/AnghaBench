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
struct TYPE_3__ {int reg_value; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int MASK_FORCE_STD ; 
 TYPE_1__* reg_fmt ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 get_register_timings(struct v4l2_dv_timings *timings)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(reg_fmt); i++) {
		if (v4l2_match_dv_timings(timings, &reg_fmt[i].format, 0,
					  false))
			return reg_fmt[i].reg_value | MASK_FORCE_STD;
	}

	return 0x0;
}