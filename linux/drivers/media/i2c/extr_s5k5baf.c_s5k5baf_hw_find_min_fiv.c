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
struct s5k5baf {int error; int fiv; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
#define  CFG_ERROR_RANGE 128 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  REG_G_ACTUAL_P_FR_TIME ; 
 int s5k5baf_get_cfg_error (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_fiv (struct s5k5baf*,int) ; 
 int s5k5baf_read (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void s5k5baf_hw_find_min_fiv(struct s5k5baf *state)
{
	u16 err, fiv;
	int n;

	fiv = s5k5baf_read(state,  REG_G_ACTUAL_P_FR_TIME);
	if (state->error)
		return;

	for (n = 5; n > 0; --n) {
		s5k5baf_hw_set_fiv(state, fiv);
		err = s5k5baf_get_cfg_error(state);
		if (state->error)
			return;
		switch (err) {
		case CFG_ERROR_RANGE:
			++fiv;
			break;
		case 0:
			state->fiv = fiv;
			v4l2_info(&state->sd,
				  "found valid frame interval: %d00us\n", fiv);
			return;
		default:
			v4l2_err(&state->sd,
				 "error setting frame interval: %d\n", err);
			state->error = -EINVAL;
		}
	}
	v4l2_err(&state->sd, "cannot find correct frame interval\n");
	state->error = -ERANGE;
}