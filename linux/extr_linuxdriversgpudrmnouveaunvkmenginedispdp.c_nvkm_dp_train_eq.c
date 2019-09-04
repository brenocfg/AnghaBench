#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct lt_state {int* stat; TYPE_4__* dp; int /*<<< orphan*/  pc2; } ;
struct TYPE_7__ {TYPE_2__* ior; } ;
struct TYPE_8__ {int* dpcd; TYPE_3__ outp; } ;
struct TYPE_5__ {int nr; } ;
struct TYPE_6__ {TYPE_1__ dp; } ;

/* Variables and functions */
 int DPCD_LS02_LANE0_CHANNEL_EQ_DONE ; 
 int DPCD_LS02_LANE0_CR_DONE ; 
 int DPCD_LS02_LANE0_SYMBOL_LOCKED ; 
 int DPCD_LS04_INTERLANE_ALIGN_DONE ; 
 size_t DPCD_RC02 ; 
 int DPCD_RC02_TPS3_SUPPORTED ; 
 scalar_t__ nvkm_dp_train_drive (struct lt_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_dp_train_pattern (struct lt_state*,int) ; 
 scalar_t__ nvkm_dp_train_sense (struct lt_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_dp_train_eq(struct lt_state *lt)
{
	bool eq_done = false, cr_done = true;
	int tries = 0, i;

	if (lt->dp->dpcd[DPCD_RC02] & DPCD_RC02_TPS3_SUPPORTED)
		nvkm_dp_train_pattern(lt, 3);
	else
		nvkm_dp_train_pattern(lt, 2);

	do {
		if ((tries &&
		    nvkm_dp_train_drive(lt, lt->pc2)) ||
		    nvkm_dp_train_sense(lt, lt->pc2, 400))
			break;

		eq_done = !!(lt->stat[2] & DPCD_LS04_INTERLANE_ALIGN_DONE);
		for (i = 0; i < lt->dp->outp.ior->dp.nr && eq_done; i++) {
			u8 lane = (lt->stat[i >> 1] >> ((i & 1) * 4)) & 0xf;
			if (!(lane & DPCD_LS02_LANE0_CR_DONE))
				cr_done = false;
			if (!(lane & DPCD_LS02_LANE0_CHANNEL_EQ_DONE) ||
			    !(lane & DPCD_LS02_LANE0_SYMBOL_LOCKED))
				eq_done = false;
		}
	} while (!eq_done && cr_done && ++tries <= 5);

	return eq_done ? 0 : -1;
}