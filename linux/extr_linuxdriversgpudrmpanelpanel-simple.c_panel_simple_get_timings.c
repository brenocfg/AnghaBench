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
struct panel_simple {TYPE_1__* desc; } ;
struct drm_panel {int dummy; } ;
struct display_timing {int dummy; } ;
struct TYPE_2__ {unsigned int num_timings; struct display_timing* timings; } ;

/* Variables and functions */
 struct panel_simple* to_panel_simple (struct drm_panel*) ; 

__attribute__((used)) static int panel_simple_get_timings(struct drm_panel *panel,
				    unsigned int num_timings,
				    struct display_timing *timings)
{
	struct panel_simple *p = to_panel_simple(panel);
	unsigned int i;

	if (p->desc->num_timings < num_timings)
		num_timings = p->desc->num_timings;

	if (timings)
		for (i = 0; i < num_timings; i++)
			timings[i] = p->desc->timings[i];

	return p->desc->num_timings;
}