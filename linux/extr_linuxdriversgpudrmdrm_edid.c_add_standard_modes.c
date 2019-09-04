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
typedef  int /*<<< orphan*/  u8 ;
struct edid {int /*<<< orphan*/ * standard_timings; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int dummy; } ;
struct detailed_mode_closure {int modes; struct edid* edid; struct drm_connector* connector; } ;

/* Variables and functions */
 int EDID_STD_TIMINGS ; 
 int /*<<< orphan*/  do_standard_modes ; 
 int /*<<< orphan*/  drm_for_each_detailed_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct detailed_mode_closure*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_std (struct drm_connector*,struct edid*,int /*<<< orphan*/ *) ; 
 scalar_t__ version_greater (struct edid*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_standard_modes(struct drm_connector *connector, struct edid *edid)
{
	int i, modes = 0;
	struct detailed_mode_closure closure = {
		.connector = connector,
		.edid = edid,
	};

	for (i = 0; i < EDID_STD_TIMINGS; i++) {
		struct drm_display_mode *newmode;

		newmode = drm_mode_std(connector, edid,
				       &edid->standard_timings[i]);
		if (newmode) {
			drm_mode_probed_add(connector, newmode);
			modes++;
		}
	}

	if (version_greater(edid, 1, 0))
		drm_for_each_detailed_block((u8 *)edid, do_standard_modes,
					    &closure);

	/* XXX should also look for standard codes in VTB blocks */

	return modes + closure.modes;
}