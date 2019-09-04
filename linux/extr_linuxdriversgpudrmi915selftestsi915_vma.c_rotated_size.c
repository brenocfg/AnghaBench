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
struct intel_rotation_plane_info {unsigned int width; unsigned int height; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int rotated_size(const struct intel_rotation_plane_info *a,
				 const struct intel_rotation_plane_info *b)
{
	return a->width * a->height + b->width * b->height;
}