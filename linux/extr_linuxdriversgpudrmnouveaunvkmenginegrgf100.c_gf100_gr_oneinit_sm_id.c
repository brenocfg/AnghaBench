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
struct gf100_gr {int tpc_max; int gpc_nr; int* tpc_nr; size_t sm_nr; TYPE_1__* sm; } ;
struct TYPE_2__ {int gpc; int tpc; } ;

/* Variables and functions */

void
gf100_gr_oneinit_sm_id(struct gf100_gr *gr)
{
	int tpc, gpc;
	for (tpc = 0; tpc < gr->tpc_max; tpc++) {
		for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
			if (tpc < gr->tpc_nr[gpc]) {
				gr->sm[gr->sm_nr].gpc = gpc;
				gr->sm[gr->sm_nr].tpc = tpc;
				gr->sm_nr++;
			}
		}
	}
}