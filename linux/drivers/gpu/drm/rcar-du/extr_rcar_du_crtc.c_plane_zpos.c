#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* state; } ;
struct rcar_du_plane {TYPE_2__ plane; } ;
struct TYPE_3__ {unsigned int normalized_zpos; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int plane_zpos(struct rcar_du_plane *plane)
{
	return plane->plane.state->normalized_zpos;
}