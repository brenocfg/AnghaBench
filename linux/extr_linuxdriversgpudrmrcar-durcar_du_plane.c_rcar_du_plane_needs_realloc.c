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
struct rcar_du_plane_state {scalar_t__ source; TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ planes; } ;

/* Variables and functions */

__attribute__((used)) static bool rcar_du_plane_needs_realloc(
				const struct rcar_du_plane_state *old_state,
				const struct rcar_du_plane_state *new_state)
{
	/*
	 * Lowering the number of planes doesn't strictly require reallocation
	 * as the extra hardware plane will be freed when committing, but doing
	 * so could lead to more fragmentation.
	 */
	if (!old_state->format ||
	    old_state->format->planes != new_state->format->planes)
		return true;

	/* Reallocate hardware planes if the source has changed. */
	if (old_state->source != new_state->source)
		return true;

	return false;
}