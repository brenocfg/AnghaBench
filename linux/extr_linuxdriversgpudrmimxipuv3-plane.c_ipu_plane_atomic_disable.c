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
struct ipu_plane {int disabling; scalar_t__ dp; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_dp_disable_channel (scalar_t__,int) ; 
 struct ipu_plane* to_ipu_plane (struct drm_plane*) ; 

__attribute__((used)) static void ipu_plane_atomic_disable(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct ipu_plane *ipu_plane = to_ipu_plane(plane);

	if (ipu_plane->dp)
		ipu_dp_disable_channel(ipu_plane->dp, true);
	ipu_plane->disabling = true;
}