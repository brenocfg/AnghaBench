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
struct s5k5baf {int error; } ;

/* Variables and functions */

__attribute__((used)) static int s5k5baf_clear_error(struct s5k5baf *state)
{
	int ret = state->error;

	state->error = 0;
	return ret;
}