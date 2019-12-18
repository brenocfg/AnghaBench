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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
struct TYPE_2__ {int* overlay_caps; } ;

/* Variables and functions */
 TYPE_1__* omap_current_dss_features ; 

enum omap_overlay_caps dss_feat_get_overlay_caps(enum omap_plane plane)
{
	return omap_current_dss_features->overlay_caps[plane];
}