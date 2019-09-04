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
struct detailed_non_pixel {scalar_t__ type; } ;
struct TYPE_2__ {struct detailed_non_pixel other_data; } ;
struct detailed_timing {TYPE_1__ data; } ;
struct detailed_mode_closure {int /*<<< orphan*/  connector; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 scalar_t__ EDID_DETAIL_EST_TIMINGS ; 
 scalar_t__ drm_est3_modes (int /*<<< orphan*/ ,struct detailed_timing*) ; 

__attribute__((used)) static void
do_established_modes(struct detailed_timing *timing, void *c)
{
	struct detailed_mode_closure *closure = c;
	struct detailed_non_pixel *data = &timing->data.other_data;

	if (data->type == EDID_DETAIL_EST_TIMINGS)
		closure->modes += drm_est3_modes(closure->connector, timing);
}