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
struct s5k5baf {int req_fiv; int fiv; scalar_t__ valid_auto_alg; scalar_t__ pixfmt; } ;

/* Variables and functions */

__attribute__((used)) static void s5k5baf_initialize_data(struct s5k5baf *state)
{
	state->pixfmt = 0;
	state->req_fiv = 10000 / 15;
	state->fiv = state->req_fiv;
	state->valid_auto_alg = 0;
}