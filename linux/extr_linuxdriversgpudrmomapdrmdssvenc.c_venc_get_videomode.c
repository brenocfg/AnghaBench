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
struct videomode {int flags; scalar_t__ pixelclock; scalar_t__ hactive; scalar_t__ vactive; } ;
typedef  enum venc_videomode { ____Placeholder_venc_videomode } venc_videomode ;
struct TYPE_4__ {scalar_t__ pixelclock; scalar_t__ hactive; scalar_t__ vactive; } ;
struct TYPE_3__ {scalar_t__ pixelclock; scalar_t__ hactive; scalar_t__ vactive; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_INTERLACED ; 
 int VENC_MODE_NTSC ; 
 int VENC_MODE_PAL ; 
 int VENC_MODE_UNKNOWN ; 
 TYPE_2__ omap_dss_ntsc_vm ; 
 TYPE_1__ omap_dss_pal_vm ; 

__attribute__((used)) static enum venc_videomode venc_get_videomode(const struct videomode *vm)
{
	if (!(vm->flags & DISPLAY_FLAGS_INTERLACED))
		return VENC_MODE_UNKNOWN;

	if (vm->pixelclock == omap_dss_pal_vm.pixelclock &&
	    vm->hactive == omap_dss_pal_vm.hactive &&
	    vm->vactive == omap_dss_pal_vm.vactive)
		return VENC_MODE_PAL;

	if (vm->pixelclock == omap_dss_ntsc_vm.pixelclock &&
	    vm->hactive == omap_dss_ntsc_vm.hactive &&
	    vm->vactive == omap_dss_ntsc_vm.vactive)
		return VENC_MODE_NTSC;

	return VENC_MODE_UNKNOWN;
}