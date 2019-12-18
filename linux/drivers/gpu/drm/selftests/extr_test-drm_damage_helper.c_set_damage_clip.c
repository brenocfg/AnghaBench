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
struct drm_mode_rect {int x1; int y1; int x2; int y2; } ;

/* Variables and functions */

__attribute__((used)) static void set_damage_clip(struct drm_mode_rect *r, int x1, int y1, int x2,
			    int y2)
{
	r->x1 = x1;
	r->y1 = y1;
	r->x2 = x2;
	r->y2 = y2;
}