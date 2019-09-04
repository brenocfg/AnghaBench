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
struct lg216x_state {int dummy; } ;

/* Variables and functions */
 int lg2160_read_lock_status (struct lg216x_state*,int*,int*) ; 

__attribute__((used)) static int lg216x_read_lock_status(struct lg216x_state *state,
				   int *acq_lock, int *sync_lock)
{
#ifdef USE_LG2161_LOCK_BITS
	int ret;
	switch (state->cfg->lg_chip) {
	case LG2160:
		ret = lg2160_read_lock_status(state, acq_lock, sync_lock);
		break;
	case LG2161:
		ret = lg2161_read_lock_status(state, acq_lock, sync_lock);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
#else
	return lg2160_read_lock_status(state, acq_lock, sync_lock);
#endif
}