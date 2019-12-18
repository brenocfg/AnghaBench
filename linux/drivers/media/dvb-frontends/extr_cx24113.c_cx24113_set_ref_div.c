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
typedef  int u8 ;
struct cx24113_state {int rev; scalar_t__ vcodiv; int refdiv; } ;

/* Variables and functions */
 scalar_t__ VCODIV4 ; 

__attribute__((used)) static u8 cx24113_set_ref_div(struct cx24113_state *state, u8 refdiv)
{
	if (state->rev == 0x43 && state->vcodiv == VCODIV4)
		refdiv = 2;
	return state->refdiv = refdiv;
}