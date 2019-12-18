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
typedef  int /*<<< orphan*/  u16 ;
struct dib0090_state {int /*<<< orphan*/  const* rf_ramp; } ;

/* Variables and functions */

__attribute__((used)) static void dib0090_set_rframp(struct dib0090_state *state, const u16 * cfg)
{
	state->rf_ramp = cfg;
}