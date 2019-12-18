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
struct ipu_plane {int disabling; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_plane_disable (struct ipu_plane*,int) ; 
 struct ipu_plane* to_ipu_plane (struct drm_plane*) ; 

void ipu_plane_disable_deferred(struct drm_plane *plane)
{
	struct ipu_plane *ipu_plane = to_ipu_plane(plane);

	if (ipu_plane->disabling) {
		ipu_plane->disabling = false;
		ipu_plane_disable(ipu_plane, false);
	}
}