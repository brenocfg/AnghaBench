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
struct gmap {unsigned long orig_asce; int edat_level; scalar_t__ removed; } ;

/* Variables and functions */

int gmap_shadow_valid(struct gmap *sg, unsigned long asce, int edat_level)
{
	if (sg->removed)
		return 0;
	return sg->orig_asce == asce && sg->edat_level == edat_level;
}