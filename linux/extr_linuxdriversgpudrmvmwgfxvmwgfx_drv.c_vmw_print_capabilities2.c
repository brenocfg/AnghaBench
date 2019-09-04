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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int SVGA_CAP2_GROW_OTABLE ; 
 int SVGA_CAP2_INTRA_SURFACE_COPY ; 

__attribute__((used)) static void vmw_print_capabilities2(uint32_t capabilities2)
{
	DRM_INFO("Capabilities2:\n");
	if (capabilities2 & SVGA_CAP2_GROW_OTABLE)
		DRM_INFO("  Grow oTable.\n");
	if (capabilities2 & SVGA_CAP2_INTRA_SURFACE_COPY)
		DRM_INFO("  IntraSurface copy.\n");
}