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
struct cardstate {scalar_t__ retry_count; int channels; TYPE_2__* bcs; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ cid; int /*<<< orphan*/  pending_commands; } ;
struct TYPE_4__ {TYPE_1__ at_state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int /*<<< orphan*/  MS_INIT ; 
 int /*<<< orphan*/  PC_CID ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_init (struct cardstate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reinit_and_retry(struct cardstate *cs, int channel)
{
	int i;

	if (--cs->retry_count <= 0)
		return -EFAULT;

	for (i = 0; i < cs->channels; ++i)
		if (cs->bcs[i].at_state.cid > 0)
			return -EBUSY;

	if (channel < 0)
		dev_warn(cs->dev,
			 "Could not enter cid mode. Reinit device and try again.\n");
	else {
		dev_warn(cs->dev,
			 "Could not get a call id. Reinit device and try again.\n");
		cs->bcs[channel].at_state.pending_commands |= PC_CID;
	}
	schedule_init(cs, MS_INIT);
	return 0;
}