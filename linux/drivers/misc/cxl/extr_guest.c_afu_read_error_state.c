#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct cxl_afu {TYPE_1__* guest; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 int H_STATE_DISABLE ; 
 int H_STATE_NORMAL ; 
 int H_STATE_PERM_UNAVAILABLE ; 
 int H_STATE_TEMP_UNAVAILABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cxl_h_read_error_state (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int afu_read_error_state(struct cxl_afu *afu, int *state_out)
{
	u64 state;
	int rc = 0;

	if (!afu)
		return -EIO;

	rc = cxl_h_read_error_state(afu->guest->handle, &state);
	if (!rc) {
		WARN_ON(state != H_STATE_NORMAL &&
			state != H_STATE_DISABLE &&
			state != H_STATE_TEMP_UNAVAILABLE &&
			state != H_STATE_PERM_UNAVAILABLE);
		*state_out = state & 0xffffffff;
	}
	return rc;
}