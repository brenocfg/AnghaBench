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
typedef  int u16 ;
struct s5k5baf {int apply_cfg; scalar_t__ error; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
#define  CFG_ERROR_RANGE 128 
 scalar_t__ EINVAL ; 
 int s5k5baf_get_cfg_error (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_find_min_fiv (struct s5k5baf*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void s5k5baf_hw_validate_cfg(struct s5k5baf *state)
{
	u16 err;

	err = s5k5baf_get_cfg_error(state);
	if (state->error)
		return;

	switch (err) {
	case 0:
		state->apply_cfg = 1;
		return;
	case CFG_ERROR_RANGE:
		s5k5baf_hw_find_min_fiv(state);
		if (!state->error)
			state->apply_cfg = 1;
		return;
	default:
		v4l2_err(&state->sd,
			 "error setting format: %d\n", err);
		state->error = -EINVAL;
	}
}