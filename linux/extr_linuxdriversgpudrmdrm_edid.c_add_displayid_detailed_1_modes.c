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
struct drm_display_mode {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct displayid_detailed_timings_1 {int dummy; } ;
struct displayid_detailed_timing_block {struct displayid_detailed_timings_1* timings; } ;
struct displayid_block {int num_bytes; } ;

/* Variables and functions */
 struct drm_display_mode* drm_mode_displayid_detailed (int /*<<< orphan*/ ,struct displayid_detailed_timings_1*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 

__attribute__((used)) static int add_displayid_detailed_1_modes(struct drm_connector *connector,
					  struct displayid_block *block)
{
	struct displayid_detailed_timing_block *det = (struct displayid_detailed_timing_block *)block;
	int i;
	int num_timings;
	struct drm_display_mode *newmode;
	int num_modes = 0;
	/* blocks must be multiple of 20 bytes length */
	if (block->num_bytes % 20)
		return 0;

	num_timings = block->num_bytes / 20;
	for (i = 0; i < num_timings; i++) {
		struct displayid_detailed_timings_1 *timings = &det->timings[i];

		newmode = drm_mode_displayid_detailed(connector->dev, timings);
		if (!newmode)
			continue;

		drm_mode_probed_add(connector, newmode);
		num_modes++;
	}
	return num_modes;
}