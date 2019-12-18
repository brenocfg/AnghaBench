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
struct dc_state {int dummy; } ;
struct dc {int /*<<< orphan*/  current_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_resource_state_copy_construct (int /*<<< orphan*/ ,struct dc_state*) ; 

void dc_resource_state_copy_construct_current(
		const struct dc *dc,
		struct dc_state *dst_ctx)
{
	dc_resource_state_copy_construct(dc->current_state, dst_ctx);
}