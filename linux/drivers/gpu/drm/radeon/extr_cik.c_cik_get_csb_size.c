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
typedef  int u32 ;
struct TYPE_2__ {struct cs_section_def* cs_data; } ;
struct radeon_device {TYPE_1__ rlc; } ;
struct cs_section_def {scalar_t__ id; struct cs_extent_def* section; } ;
struct cs_extent_def {scalar_t__ reg_count; int /*<<< orphan*/ * extent; } ;

/* Variables and functions */
 scalar_t__ SECT_CONTEXT ; 

u32 cik_get_csb_size(struct radeon_device *rdev)
{
	u32 count = 0;
	const struct cs_section_def *sect = NULL;
	const struct cs_extent_def *ext = NULL;

	if (rdev->rlc.cs_data == NULL)
		return 0;

	/* begin clear state */
	count += 2;
	/* context control state */
	count += 3;

	for (sect = rdev->rlc.cs_data; sect->section != NULL; ++sect) {
		for (ext = sect->section; ext->extent != NULL; ++ext) {
			if (sect->id == SECT_CONTEXT)
				count += 2 + ext->reg_count;
			else
				return 0;
		}
	}
	/* pa_sc_raster_config/pa_sc_raster_config1 */
	count += 4;
	/* end clear state */
	count += 2;
	/* clear state */
	count += 2;

	return count;
}