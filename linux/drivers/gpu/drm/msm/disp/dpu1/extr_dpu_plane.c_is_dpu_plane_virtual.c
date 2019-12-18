#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_plane {int dummy; } ;
struct TYPE_2__ {int is_virtual; } ;

/* Variables and functions */
 TYPE_1__* to_dpu_plane (struct drm_plane*) ; 

bool is_dpu_plane_virtual(struct drm_plane *plane)
{
	return plane ? to_dpu_plane(plane)->is_virtual : false;
}