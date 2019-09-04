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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_property {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mdp4_plane_set_property(struct drm_plane *plane,
		struct drm_property *property, uint64_t val)
{
	// XXX
	return -EINVAL;
}