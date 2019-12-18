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
struct vc4_shader_validation_state {scalar_t__* tmu_write_count; } ;

/* Variables and functions */

__attribute__((used)) static bool
texturing_in_progress(struct vc4_shader_validation_state *validation_state)
{
	return (validation_state->tmu_write_count[0] != 0 ||
		validation_state->tmu_write_count[1] != 0);
}