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
struct TYPE_6__ {int /*<<< orphan*/  pending_commands; } ;
struct cardstate {int mstate; int channels; int mode; TYPE_2__* bcs; TYPE_3__ at_state; int /*<<< orphan*/  temp_at_states; int /*<<< orphan*/  cur_at_seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending_commands; } ;
struct TYPE_5__ {TYPE_1__ at_state; } ;

/* Variables and functions */
 int EBUSY ; 
#define  MS_LOCKED 130 
#define  MS_READY 129 
#define  MS_UNINITIALIZED 128 
 int M_UNKNOWN ; 
 int /*<<< orphan*/  gigaset_get_channels (struct cardstate*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_lock(struct cardstate *cs)
{
	int mode;
	int i;

	switch (cs->mstate) {
	case MS_UNINITIALIZED:
	case MS_READY:
		if (cs->cur_at_seq || !list_empty(&cs->temp_at_states) ||
		    cs->at_state.pending_commands)
			return -EBUSY;

		for (i = 0; i < cs->channels; ++i)
			if (cs->bcs[i].at_state.pending_commands)
				return -EBUSY;

		if (gigaset_get_channels(cs) < 0)
			return -EBUSY;

		break;
	case MS_LOCKED:
		break;
	default:
		return -EBUSY;
	}

	mode = cs->mode;
	cs->mstate = MS_LOCKED;
	cs->mode = M_UNKNOWN;

	return mode;
}