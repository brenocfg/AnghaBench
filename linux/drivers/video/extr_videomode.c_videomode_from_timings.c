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
struct videomode {int dummy; } ;
struct display_timings {int dummy; } ;
struct display_timing {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct display_timing* display_timings_get (struct display_timings const*,unsigned int) ; 
 int /*<<< orphan*/  videomode_from_timing (struct display_timing*,struct videomode*) ; 

int videomode_from_timings(const struct display_timings *disp,
			  struct videomode *vm, unsigned int index)
{
	struct display_timing *dt;

	dt = display_timings_get(disp, index);
	if (!dt)
		return -EINVAL;

	videomode_from_timing(dt, vm);

	return 0;
}