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
struct drm_plane {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_OVERLAY ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 

__attribute__((used)) static int
nv50_wndw_zpos_default(struct drm_plane *plane)
{
	return (plane->type == DRM_PLANE_TYPE_PRIMARY) ? 0 :
	       (plane->type == DRM_PLANE_TYPE_OVERLAY) ? 1 : 255;
}