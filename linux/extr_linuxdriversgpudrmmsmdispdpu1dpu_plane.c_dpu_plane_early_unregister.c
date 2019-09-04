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
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_plane_destroy_debugfs (struct drm_plane*) ; 

__attribute__((used)) static void dpu_plane_early_unregister(struct drm_plane *plane)
{
	_dpu_plane_destroy_debugfs(plane);
}