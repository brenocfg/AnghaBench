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
struct mxl111sf_demod_state {int dummy; } ;

/* Variables and functions */
 int SYNC_LOCK_MASK ; 
 int /*<<< orphan*/  V6_SYNC_LOCK_REG ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static
int mxl1x1sf_demod_get_sync_lock_status(struct mxl111sf_demod_state *state,
					int *sync_lock)
{
	u8 val = 0;
	int ret = mxl111sf_demod_read_reg(state, V6_SYNC_LOCK_REG, &val);
	if (mxl_fail(ret))
		goto fail;
	*sync_lock = (val & SYNC_LOCK_MASK) >> 4;
fail:
	return ret;
}