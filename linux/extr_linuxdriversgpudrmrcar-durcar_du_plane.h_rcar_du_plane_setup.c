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
struct rcar_du_plane_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct rcar_du_plane {int /*<<< orphan*/  group; TYPE_1__ plane; } ;

/* Variables and functions */
 void __rcar_du_plane_setup (int /*<<< orphan*/ ,struct rcar_du_plane_state*) ; 
 struct rcar_du_plane_state* to_rcar_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rcar_du_plane_setup(struct rcar_du_plane *plane)
{
	struct rcar_du_plane_state *state =
		to_rcar_plane_state(plane->plane.state);

	return __rcar_du_plane_setup(plane->group, state);
}