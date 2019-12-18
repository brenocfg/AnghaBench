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
struct nvkm_i2c_aux {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct nvkm_dp {int present; TYPE_1__ lt; int /*<<< orphan*/  outp; int /*<<< orphan*/  dpcd; struct nvkm_i2c_aux* aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCD_RC00_DPCD_REV ; 
 int /*<<< orphan*/  OUTP_DBG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_i2c_aux_monitor (struct nvkm_i2c_aux*,int) ; 
 int /*<<< orphan*/  nvkm_rdaux (struct nvkm_i2c_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
nvkm_dp_enable(struct nvkm_dp *dp, bool enable)
{
	struct nvkm_i2c_aux *aux = dp->aux;

	if (enable) {
		if (!dp->present) {
			OUTP_DBG(&dp->outp, "aux power -> always");
			nvkm_i2c_aux_monitor(aux, true);
			dp->present = true;
		}

		if (!nvkm_rdaux(aux, DPCD_RC00_DPCD_REV, dp->dpcd,
				sizeof(dp->dpcd)))
			return true;
	}

	if (dp->present) {
		OUTP_DBG(&dp->outp, "aux power -> demand");
		nvkm_i2c_aux_monitor(aux, false);
		dp->present = false;
	}

	atomic_set(&dp->lt.done, 0);
	return false;
}