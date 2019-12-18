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
struct drm_plane_state {scalar_t__ zpos; TYPE_1__* plane; } ;
struct TYPE_4__ {int id; } ;
struct TYPE_3__ {TYPE_2__ base; } ;

/* Variables and functions */

__attribute__((used)) static int drm_atomic_state_zpos_cmp(const void *a, const void *b)
{
	const struct drm_plane_state *sa = *(struct drm_plane_state **)a;
	const struct drm_plane_state *sb = *(struct drm_plane_state **)b;

	if (sa->zpos != sb->zpos)
		return sa->zpos - sb->zpos;
	else
		return sa->plane->base.id - sb->plane->base.id;
}