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
struct dib0090_state {int bb_1_def; } ;

/* Variables and functions */

__attribute__((used)) static void dib0090_set_boost(struct dib0090_state *state, int onoff)
{
	state->bb_1_def &= 0xdfff;
	state->bb_1_def |= onoff << 13;
}