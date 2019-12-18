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
struct malidp_plane {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  kfree (struct malidp_plane*) ; 
 struct malidp_plane* to_malidp_plane (struct drm_plane*) ; 

__attribute__((used)) static void malidp_de_plane_destroy(struct drm_plane *plane)
{
	struct malidp_plane *mp = to_malidp_plane(plane);

	drm_plane_cleanup(plane);
	kfree(mp);
}