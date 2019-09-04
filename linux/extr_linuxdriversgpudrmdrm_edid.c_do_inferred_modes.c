#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct detailed_data_monitor_range {int flags; } ;
struct TYPE_4__ {struct detailed_data_monitor_range range; } ;
struct detailed_non_pixel {scalar_t__ type; TYPE_2__ data; } ;
struct TYPE_3__ {struct detailed_non_pixel other_data; } ;
struct detailed_timing {TYPE_1__ data; } ;
struct detailed_mode_closure {int /*<<< orphan*/  edid; int /*<<< orphan*/  connector; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 scalar_t__ EDID_DETAIL_MONITOR_RANGE ; 
 int /*<<< orphan*/  drm_cvt_modes_for_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct detailed_timing*) ; 
 scalar_t__ drm_dmt_modes_for_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct detailed_timing*) ; 
 int /*<<< orphan*/  drm_gtf_modes_for_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct detailed_timing*) ; 
 int /*<<< orphan*/  version_greater (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
do_inferred_modes(struct detailed_timing *timing, void *c)
{
	struct detailed_mode_closure *closure = c;
	struct detailed_non_pixel *data = &timing->data.other_data;
	struct detailed_data_monitor_range *range = &data->data.range;

	if (data->type != EDID_DETAIL_MONITOR_RANGE)
		return;

	closure->modes += drm_dmt_modes_for_range(closure->connector,
						  closure->edid,
						  timing);
	
	if (!version_greater(closure->edid, 1, 1))
		return; /* GTF not defined yet */

	switch (range->flags) {
	case 0x02: /* secondary gtf, XXX could do more */
	case 0x00: /* default gtf */
		closure->modes += drm_gtf_modes_for_range(closure->connector,
							  closure->edid,
							  timing);
		break;
	case 0x04: /* cvt, only in 1.4+ */
		if (!version_greater(closure->edid, 1, 3))
			break;

		closure->modes += drm_cvt_modes_for_range(closure->connector,
							  closure->edid,
							  timing);
		break;
	case 0x01: /* just the ranges, no formula */
	default:
		break;
	}
}