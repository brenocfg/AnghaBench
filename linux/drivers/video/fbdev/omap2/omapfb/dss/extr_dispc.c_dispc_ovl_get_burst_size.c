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
typedef  unsigned int u32 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;

/* Variables and functions */
 unsigned int dss_feat_get_burst_size_unit () ; 

__attribute__((used)) static u32 dispc_ovl_get_burst_size(enum omap_plane plane)
{
	unsigned unit = dss_feat_get_burst_size_unit();
	/* burst multiplier is always x8 (see dispc_configure_burst_sizes()) */
	return unit * 8;
}