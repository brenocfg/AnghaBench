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
typedef  scalar_t__ u64 ;
struct drm_printer {int dummy; } ;
struct drm_mm_node {scalar_t__ hole_size; } ;

/* Variables and functions */
 scalar_t__ drm_mm_hole_node_start (struct drm_mm_node const*) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u64 drm_mm_dump_hole(struct drm_printer *p, const struct drm_mm_node *entry)
{
	u64 start, size;

	size = entry->hole_size;
	if (size) {
		start = drm_mm_hole_node_start(entry);
		drm_printf(p, "%#018llx-%#018llx: %llu: free\n",
			   start, start + size, size);
	}

	return size;
}