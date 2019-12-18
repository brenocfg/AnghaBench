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
typedef  scalar_t__ uint32_t ;
struct dc_plane_state {scalar_t__ irq_source; } ;

/* Variables and functions */
 scalar_t__ DC_IRQ_SOURCE_PFLIP1 ; 

void enable_surface_flip_reporting(struct dc_plane_state *plane_state,
		uint32_t controller_id)
{
	plane_state->irq_source = controller_id + DC_IRQ_SOURCE_PFLIP1 - 1;
	/*register_flip_interrupt(surface);*/
}