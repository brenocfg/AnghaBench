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
struct lt_state {int* conf; int* stat; TYPE_4__* dp; } ;
struct TYPE_7__ {TYPE_2__* ior; } ;
struct TYPE_8__ {TYPE_3__ outp; } ;
struct TYPE_5__ {int nr; } ;
struct TYPE_6__ {TYPE_1__ dp; } ;

/* Variables and functions */
 int DPCD_LC03_MAX_SWING_REACHED ; 
 int DPCD_LC03_VOLTAGE_SWING_SET ; 
 int DPCD_LS02_LANE0_CR_DONE ; 
 scalar_t__ nvkm_dp_train_drive (struct lt_state*,int) ; 
 int /*<<< orphan*/  nvkm_dp_train_pattern (struct lt_state*,int) ; 
 scalar_t__ nvkm_dp_train_sense (struct lt_state*,int,int) ; 

__attribute__((used)) static int
nvkm_dp_train_cr(struct lt_state *lt)
{
	bool cr_done = false, abort = false;
	int voltage = lt->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET;
	int tries = 0, i;

	nvkm_dp_train_pattern(lt, 1);

	do {
		if (nvkm_dp_train_drive(lt, false) ||
		    nvkm_dp_train_sense(lt, false, 100))
			break;

		cr_done = true;
		for (i = 0; i < lt->dp->outp.ior->dp.nr; i++) {
			u8 lane = (lt->stat[i >> 1] >> ((i & 1) * 4)) & 0xf;
			if (!(lane & DPCD_LS02_LANE0_CR_DONE)) {
				cr_done = false;
				if (lt->conf[i] & DPCD_LC03_MAX_SWING_REACHED)
					abort = true;
				break;
			}
		}

		if ((lt->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET) != voltage) {
			voltage = lt->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET;
			tries = 0;
		}
	} while (!cr_done && !abort && ++tries < 5);

	return cr_done ? 0 : -1;
}