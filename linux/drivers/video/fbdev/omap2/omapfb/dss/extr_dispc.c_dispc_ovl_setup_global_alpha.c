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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_GLOBAL_ALPHA ; 
 int OMAP_DSS_OVL_CAP_GLOBAL_ALPHA ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dispc_ovl_setup_global_alpha(enum omap_plane plane,
		enum omap_overlay_caps caps, u8 global_alpha)
{
	static const unsigned shifts[] = { 0, 8, 16, 24, };
	int shift;

	if ((caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
		return;

	shift = shifts[plane];
	REG_FLD_MOD(DISPC_GLOBAL_ALPHA, global_alpha, shift + 7, shift);
}