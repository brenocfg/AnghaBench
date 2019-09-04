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
struct dispc_device {TYPE_1__* feat; } ;
struct TYPE_2__ {int sw_max; int hp_max; int vp_max; } ;

/* Variables and functions */

__attribute__((used)) static bool _dispc_lcd_timings_ok(struct dispc_device *dispc,
				  int hsync_len, int hfp, int hbp,
				  int vsw, int vfp, int vbp)
{
	if (hsync_len < 1 || hsync_len > dispc->feat->sw_max ||
	    hfp < 1 || hfp > dispc->feat->hp_max ||
	    hbp < 1 || hbp > dispc->feat->hp_max ||
	    vsw < 1 || vsw > dispc->feat->sw_max ||
	    vfp < 0 || vfp > dispc->feat->vp_max ||
	    vbp < 0 || vbp > dispc->feat->vp_max)
		return false;
	return true;
}