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
struct TYPE_2__ {int x1; int y1; int x2; int y2; } ;
struct drm_plane_state {TYPE_1__ src; } ;

/* Variables and functions */

__attribute__((used)) static void set_plane_src(struct drm_plane_state *state, int x1, int y1, int x2,
			  int y2)
{
	state->src.x1 = x1;
	state->src.y1 = y1;
	state->src.x2 = x2;
	state->src.y2 = y2;
}