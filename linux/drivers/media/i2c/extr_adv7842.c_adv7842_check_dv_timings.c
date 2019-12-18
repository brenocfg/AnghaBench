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
struct v4l2_dv_timings {int dummy; } ;
struct TYPE_4__ {scalar_t__ width; } ;
struct TYPE_5__ {TYPE_1__ bt; } ;

/* Variables and functions */
 TYPE_2__* adv7842_timings_exceptions ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings const*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool adv7842_check_dv_timings(const struct v4l2_dv_timings *t, void *hdl)
{
	int i;

	for (i = 0; adv7842_timings_exceptions[i].bt.width; i++)
		if (v4l2_match_dv_timings(t, adv7842_timings_exceptions + i, 0, false))
			return false;
	return true;
}