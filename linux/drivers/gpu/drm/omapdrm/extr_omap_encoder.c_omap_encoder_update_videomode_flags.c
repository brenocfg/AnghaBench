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
typedef  int u32 ;
struct videomode {int flags; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DE_HIGH ; 
 int DISPLAY_FLAGS_DE_LOW ; 
 int DISPLAY_FLAGS_PIXDATA_NEGEDGE ; 
 int DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int DISPLAY_FLAGS_SYNC_NEGEDGE ; 
 int DISPLAY_FLAGS_SYNC_POSEDGE ; 
 int DRM_BUS_FLAG_DE_HIGH ; 
 int DRM_BUS_FLAG_DE_LOW ; 
 int DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE ; 
 int DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE ; 
 int DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE ; 
 int DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE ; 

__attribute__((used)) static void omap_encoder_update_videomode_flags(struct videomode *vm,
						u32 bus_flags)
{
	if (!(vm->flags & (DISPLAY_FLAGS_DE_LOW |
			   DISPLAY_FLAGS_DE_HIGH))) {
		if (bus_flags & DRM_BUS_FLAG_DE_LOW)
			vm->flags |= DISPLAY_FLAGS_DE_LOW;
		else if (bus_flags & DRM_BUS_FLAG_DE_HIGH)
			vm->flags |= DISPLAY_FLAGS_DE_HIGH;
	}

	if (!(vm->flags & (DISPLAY_FLAGS_PIXDATA_POSEDGE |
			   DISPLAY_FLAGS_PIXDATA_NEGEDGE))) {
		if (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE)
			vm->flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE;
		else if (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
			vm->flags |= DISPLAY_FLAGS_PIXDATA_NEGEDGE;
	}

	if (!(vm->flags & (DISPLAY_FLAGS_SYNC_POSEDGE |
			   DISPLAY_FLAGS_SYNC_NEGEDGE))) {
		if (bus_flags & DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE)
			vm->flags |= DISPLAY_FLAGS_SYNC_POSEDGE;
		else if (bus_flags & DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE)
			vm->flags |= DISPLAY_FLAGS_SYNC_NEGEDGE;
	}
}