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
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;
struct TYPE_2__ {int supported_rotation_types; } ;

/* Variables and functions */
 TYPE_1__* omap_current_dss_features ; 

bool dss_feat_rotation_type_supported(enum omap_dss_rotation_type rot_type)
{
	return omap_current_dss_features->supported_rotation_types & rot_type;
}