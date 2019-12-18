#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_dp {int* dpcd; int /*<<< orphan*/  outp; int /*<<< orphan*/  aux; } ;
struct lt_state {int* stat; int pc2stat; struct nvkm_dp* dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCD_LS02 ; 
 int /*<<< orphan*/  DPCD_LS0C ; 
 size_t DPCD_RC0E_AUX_RD_INTERVAL ; 
 int /*<<< orphan*/  OUTP_TRACE (int /*<<< orphan*/ *,char*,int*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int nvkm_rdaux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_dp_train_sense(struct lt_state *lt, bool pc, u32 delay)
{
	struct nvkm_dp *dp = lt->dp;
	int ret;

	if (dp->dpcd[DPCD_RC0E_AUX_RD_INTERVAL])
		mdelay(dp->dpcd[DPCD_RC0E_AUX_RD_INTERVAL] * 4);
	else
		udelay(delay);

	ret = nvkm_rdaux(dp->aux, DPCD_LS02, lt->stat, 6);
	if (ret)
		return ret;

	if (pc) {
		ret = nvkm_rdaux(dp->aux, DPCD_LS0C, &lt->pc2stat, 1);
		if (ret)
			lt->pc2stat = 0x00;
		OUTP_TRACE(&dp->outp, "status %6ph pc2 %02x",
			   lt->stat, lt->pc2stat);
	} else {
		OUTP_TRACE(&dp->outp, "status %6ph", lt->stat);
	}

	return 0;
}