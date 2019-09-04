#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_check_dv_timings_fnc ;
typedef  size_t u32 ;
struct TYPE_4__ {scalar_t__ width; } ;
struct TYPE_5__ {TYPE_1__ bt; } ;
struct v4l2_enum_dv_timings {scalar_t__ index; TYPE_2__ timings; int /*<<< orphan*/  reserved; } ;
struct v4l2_dv_timings_cap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* v4l2_dv_timings_presets ; 
 scalar_t__ v4l2_valid_dv_timings (TYPE_2__*,struct v4l2_dv_timings_cap const*,int /*<<< orphan*/ ,void*) ; 

int v4l2_enum_dv_timings_cap(struct v4l2_enum_dv_timings *t,
			     const struct v4l2_dv_timings_cap *cap,
			     v4l2_check_dv_timings_fnc fnc,
			     void *fnc_handle)
{
	u32 i, idx;

	memset(t->reserved, 0, sizeof(t->reserved));
	for (i = idx = 0; v4l2_dv_timings_presets[i].bt.width; i++) {
		if (v4l2_valid_dv_timings(v4l2_dv_timings_presets + i, cap,
					  fnc, fnc_handle) &&
		    idx++ == t->index) {
			t->timings = v4l2_dv_timings_presets[i];
			return 0;
		}
	}
	return -EINVAL;
}