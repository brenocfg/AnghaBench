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
struct dst_state {int modulation; } ;
typedef  enum fe_modulation { ____Placeholder_fe_modulation } fe_modulation ;

/* Variables and functions */

__attribute__((used)) static enum fe_modulation dst_get_modulation(struct dst_state *state)
{
	return state->modulation;
}