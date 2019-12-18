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
typedef  enum omap_display_type { ____Placeholder_omap_display_type } omap_display_type ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int* supported_displays; } ;

/* Variables and functions */
 TYPE_1__* omap_current_dss_features ; 

enum omap_display_type dss_feat_get_supported_displays(enum omap_channel channel)
{
	return omap_current_dss_features->supported_displays[channel];
}