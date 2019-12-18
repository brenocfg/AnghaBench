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
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;

/* Variables and functions */

__attribute__((used)) static inline void elevate_update_type(enum surface_update_type *original, enum surface_update_type new)
{
	if (new > *original)
		*original = new;
}