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
typedef  scalar_t__ uint8_t ;
typedef  size_t u32 ;
struct mdp5_smp_state {void* state; void** client_state; } ;
struct mdp5_smp {int blk_cnt; TYPE_1__* dev; scalar_t__* reserved; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bitmap_weight (void*,int) ; 
 int find_first_zero_bit (void*,int) ; 
 int max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 

__attribute__((used)) static int smp_request_block(struct mdp5_smp *smp,
		struct mdp5_smp_state *state,
		u32 cid, int nblks)
{
	void *cs = state->client_state[cid];
	int i, avail, cnt = smp->blk_cnt;
	uint8_t reserved;

	/* we shouldn't be requesting blocks for an in-use client: */
	WARN_ON(bitmap_weight(cs, cnt) > 0);

	reserved = smp->reserved[cid];

	if (reserved) {
		nblks = max(0, nblks - reserved);
		DBG("%d MMBs allocated (%d reserved)", nblks, reserved);
	}

	avail = cnt - bitmap_weight(state->state, cnt);
	if (nblks > avail) {
		DRM_DEV_ERROR(smp->dev->dev, "out of blks (req=%d > avail=%d)\n",
				nblks, avail);
		return -ENOSPC;
	}

	for (i = 0; i < nblks; i++) {
		int blk = find_first_zero_bit(state->state, cnt);
		set_bit(blk, cs);
		set_bit(blk, state->state);
	}

	return 0;
}