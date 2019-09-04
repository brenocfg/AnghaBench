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
struct sha512_mb_mgr {int* lens; int unused_lanes; TYPE_1__* ldata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * job_in_lane; } ;

/* Variables and functions */

void sha512_mb_mgr_init_avx2(struct sha512_mb_mgr *state)
{
	unsigned int j;

	/* initially all lanes are unused */
	state->lens[0] = 0xFFFFFFFF00000000;
	state->lens[1] = 0xFFFFFFFF00000001;
	state->lens[2] = 0xFFFFFFFF00000002;
	state->lens[3] = 0xFFFFFFFF00000003;

	state->unused_lanes = 0xFF03020100;
	for (j = 0; j < 4; j++)
		state->ldata[j].job_in_lane = NULL;
}