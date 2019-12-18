#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cpa; int /*<<< orphan*/  pfch; } ;
union orb {TYPE_2__ cmd; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int c64; } ;
struct TYPE_6__ {TYPE_1__ cmd; } ;
struct channel_program {int initialized; TYPE_3__ orb; struct device* mdev; int /*<<< orphan*/  ccwchain_list; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ccwchain_handle_ccw (int /*<<< orphan*/ ,struct channel_program*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,union orb*,int) ; 

int cp_init(struct channel_program *cp, struct device *mdev, union orb *orb)
{
	int ret;

	/*
	 * XXX:
	 * Only support prefetch enable mode now.
	 */
	if (!orb->cmd.pfch)
		return -EOPNOTSUPP;

	INIT_LIST_HEAD(&cp->ccwchain_list);
	memcpy(&cp->orb, orb, sizeof(*orb));
	cp->mdev = mdev;

	/* Build a ccwchain for the first CCW segment */
	ret = ccwchain_handle_ccw(orb->cmd.cpa, cp);

	if (!ret) {
		cp->initialized = true;

		/* It is safe to force: if it was not set but idals used
		 * ccwchain_calc_length would have returned an error.
		 */
		cp->orb.cmd.c64 = 1;
	}

	return ret;
}