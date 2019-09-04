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
typedef  int u32 ;
struct cs_section_def {scalar_t__ id; struct cs_extent_def* section; } ;
struct cs_extent_def {scalar_t__ reg_count; int /*<<< orphan*/ * extent; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SECT_CONTEXT ; 
 struct cs_section_def* gfx9_cs_data ; 

__attribute__((used)) static u32 gfx_v9_0_get_csb_size(struct amdgpu_device *adev)
{
	u32 count = 0;
	const struct cs_section_def *sect = NULL;
	const struct cs_extent_def *ext = NULL;

	/* begin clear state */
	count += 2;
	/* context control state */
	count += 3;

	for (sect = gfx9_cs_data; sect->section != NULL; ++sect) {
		for (ext = sect->section; ext->extent != NULL; ++ext) {
			if (sect->id == SECT_CONTEXT)
				count += 2 + ext->reg_count;
			else
				return 0;
		}
	}

	/* end clear state */
	count += 2;
	/* clear state */
	count += 2;

	return count;
}