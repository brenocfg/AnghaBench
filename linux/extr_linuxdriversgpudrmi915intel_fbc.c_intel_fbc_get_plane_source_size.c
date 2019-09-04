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
struct TYPE_2__ {int src_w; int src_h; } ;
struct intel_fbc_state_cache {TYPE_1__ plane; } ;

/* Variables and functions */

__attribute__((used)) static void intel_fbc_get_plane_source_size(struct intel_fbc_state_cache *cache,
					    int *width, int *height)
{
	if (width)
		*width = cache->plane.src_w;
	if (height)
		*height = cache->plane.src_h;
}