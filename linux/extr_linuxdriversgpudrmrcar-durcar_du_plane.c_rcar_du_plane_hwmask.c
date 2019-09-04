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
struct rcar_du_plane_state {int hwindex; TYPE_1__* format; } ;
struct TYPE_2__ {int planes; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int rcar_du_plane_hwmask(struct rcar_du_plane_state *state)
{
	unsigned int mask;

	if (state->hwindex == -1)
		return 0;

	mask = 1 << state->hwindex;
	if (state->format->planes == 2)
		mask |= 1 << ((state->hwindex + 1) % 8);

	return mask;
}