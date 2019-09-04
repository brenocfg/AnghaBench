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
struct std_timing {int dummy; } ;
struct edid {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_3__ {struct std_timing* timings; } ;
struct detailed_non_pixel {scalar_t__ type; TYPE_1__ data; } ;
struct TYPE_4__ {struct detailed_non_pixel other_data; } ;
struct detailed_timing {TYPE_2__ data; } ;
struct detailed_mode_closure {int /*<<< orphan*/  modes; struct edid* edid; struct drm_connector* connector; } ;

/* Variables and functions */
 scalar_t__ EDID_DETAIL_STD_MODES ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_std (struct drm_connector*,struct edid*,struct std_timing*) ; 

__attribute__((used)) static void
do_standard_modes(struct detailed_timing *timing, void *c)
{
	struct detailed_mode_closure *closure = c;
	struct detailed_non_pixel *data = &timing->data.other_data;
	struct drm_connector *connector = closure->connector;
	struct edid *edid = closure->edid;

	if (data->type == EDID_DETAIL_STD_MODES) {
		int i;
		for (i = 0; i < 6; i++) {
			struct std_timing *std;
			struct drm_display_mode *newmode;

			std = &data->data.timings[i];
			newmode = drm_mode_std(connector, edid, std);
			if (newmode) {
				drm_mode_probed_add(connector, newmode);
				closure->modes++;
			}
		}
	}
}