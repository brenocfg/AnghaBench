#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ena; } ;
struct TYPE_4__ {int /*<<< orphan*/  scsw; TYPE_1__ pmcw; } ;
struct subchannel {TYPE_2__ schib; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int SCSW_ACTL_CLEAR_PEND ; 
 int SCSW_ACTL_HALT_PEND ; 
 int cio_cancel (struct subchannel*) ; 
 int cio_clear (struct subchannel*) ; 
 int cio_halt (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int scsw_actl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_is_tm (int /*<<< orphan*/ *) ; 

int cio_cancel_halt_clear(struct subchannel *sch, int *iretry)
{
	int ret;

	if (cio_update_schib(sch))
		return -ENODEV;
	if (!sch->schib.pmcw.ena)
		/* Not operational -> done. */
		return 0;
	/* Stage 1: cancel io. */
	if (!(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_HALT_PEND) &&
	    !(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_CLEAR_PEND)) {
		if (!scsw_is_tm(&sch->schib.scsw)) {
			ret = cio_cancel(sch);
			if (ret != -EINVAL)
				return ret;
		}
		/*
		 * Cancel io unsuccessful or not applicable (transport mode).
		 * Continue with asynchronous instructions.
		 */
		*iretry = 3;	/* 3 halt retries. */
	}
	/* Stage 2: halt io. */
	if (!(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_CLEAR_PEND)) {
		if (*iretry) {
			*iretry -= 1;
			ret = cio_halt(sch);
			if (ret != -EBUSY)
				return (ret == 0) ? -EBUSY : ret;
		}
		/* Halt io unsuccessful. */
		*iretry = 255;	/* 255 clear retries. */
	}
	/* Stage 3: clear io. */
	if (*iretry) {
		*iretry -= 1;
		ret = cio_clear(sch);
		return (ret == 0) ? -EBUSY : ret;
	}
	/* Function was unsuccessful */
	return -EIO;
}