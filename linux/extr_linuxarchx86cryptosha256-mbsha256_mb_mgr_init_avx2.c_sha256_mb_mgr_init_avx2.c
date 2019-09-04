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
struct sha256_mb_mgr {int unused_lanes; int* lens; TYPE_1__* ldata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * job_in_lane; } ;

/* Variables and functions */

void sha256_mb_mgr_init_avx2(struct sha256_mb_mgr *state)
{
	unsigned int j;

	state->unused_lanes = 0xF76543210ULL;
	for (j = 0; j < 8; j++) {
		state->lens[j] = 0xFFFFFFFF;
		state->ldata[j].job_in_lane = NULL;
	}
}