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
struct TYPE_4__ {TYPE_1__* edid_blob_ptr; } ;
struct tegra_output {TYPE_2__ connector; } ;
struct edid {int dummy; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int drm_detect_hdmi_monitor (struct edid*) ; 

__attribute__((used)) static bool tegra_output_is_hdmi(struct tegra_output *output)
{
	struct edid *edid;

	if (!output->connector.edid_blob_ptr)
		return false;

	edid = (struct edid *)output->connector.edid_blob_ptr->data;

	return drm_detect_hdmi_monitor(edid);
}