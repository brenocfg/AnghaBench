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
struct vega12_dpm_state {int soft_min_level; int soft_max_level; int hard_min_level; int hard_max_level; } ;

/* Variables and functions */

__attribute__((used)) static void vega12_init_dpm_state(struct vega12_dpm_state *dpm_state)
{
	dpm_state->soft_min_level = 0x0;
	dpm_state->soft_max_level = 0xffff;
	dpm_state->hard_min_level = 0x0;
	dpm_state->hard_max_level = 0xffff;
}