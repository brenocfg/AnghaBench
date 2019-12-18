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
struct shmob_drm_plane {int dummy; } ;
struct drm_plane {int /*<<< orphan*/ * fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __shmob_drm_plane_setup (struct shmob_drm_plane*,int /*<<< orphan*/ *) ; 
 struct shmob_drm_plane* to_shmob_plane (struct drm_plane*) ; 

void shmob_drm_plane_setup(struct drm_plane *plane)
{
	struct shmob_drm_plane *splane = to_shmob_plane(plane);

	if (plane->fb == NULL)
		return;

	__shmob_drm_plane_setup(splane, plane->fb);
}