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
typedef  int /*<<< orphan*/  u16 ;
struct sseu_dev_info {int max_slices; int max_subslices; int /*<<< orphan*/ * subslice_mask; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,...) ; 
 int /*<<< orphan*/  hweight16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sseu_subslices_per_slice (struct sseu_dev_info const*,int) ; 
 int /*<<< orphan*/  sseu_get_eus (struct sseu_dev_info const*,int,int) ; 

void intel_device_info_dump_topology(const struct sseu_dev_info *sseu,
				     struct drm_printer *p)
{
	int s, ss;

	if (sseu->max_slices == 0) {
		drm_printf(p, "Unavailable\n");
		return;
	}

	for (s = 0; s < sseu->max_slices; s++) {
		drm_printf(p, "slice%d: %u subslice(s) (0x%hhx):\n",
			   s, intel_sseu_subslices_per_slice(sseu, s),
			   sseu->subslice_mask[s]);

		for (ss = 0; ss < sseu->max_subslices; ss++) {
			u16 enabled_eus = sseu_get_eus(sseu, s, ss);

			drm_printf(p, "\tsubslice%d: %u EUs (0x%hx)\n",
				   ss, hweight16(enabled_eus), enabled_eus);
		}
	}
}