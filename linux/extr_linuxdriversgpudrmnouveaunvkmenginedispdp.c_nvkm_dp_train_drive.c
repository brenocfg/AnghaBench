#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {int nr; } ;
struct nvkm_ior {TYPE_8__* func; TYPE_5__ dp; TYPE_4__* disp; } ;
struct TYPE_15__ {int /*<<< orphan*/  hashm; int /*<<< orphan*/  hasht; } ;
struct TYPE_18__ {TYPE_6__ info; struct nvkm_ior* ior; } ;
struct nvkm_dp {int /*<<< orphan*/  aux; TYPE_9__ outp; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_dpout {int dummy; } ;
struct nvbios_dpcfg {int /*<<< orphan*/  tx_pu; int /*<<< orphan*/  pe; int /*<<< orphan*/  dc; int /*<<< orphan*/  pc; } ;
struct lt_state {int* stat; int pc2stat; int* conf; int* pc2conf; struct nvkm_dp* dp; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* drive ) (struct nvkm_ior*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_7__ dp; } ;
struct TYPE_11__ {TYPE_1__* device; } ;
struct TYPE_12__ {TYPE_2__ subdev; } ;
struct TYPE_13__ {TYPE_3__ engine; } ;
struct TYPE_10__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCD_LC03 (int /*<<< orphan*/ ) ; 
 int DPCD_LC03_MAX_SWING_REACHED ; 
 int /*<<< orphan*/  DPCD_LC0F ; 
 int DPCD_LC0F_LANE0_MAX_POST_CURSOR2_REACHED ; 
 int /*<<< orphan*/  OUTP_TRACE (TYPE_9__*,char*,int,int,int) ; 
 int /*<<< orphan*/  nvbios_dpcfg_match (struct nvkm_bios*,int /*<<< orphan*/ ,int,int,int,int*,int*,int*,int*,struct nvbios_dpcfg*) ; 
 int /*<<< orphan*/  nvbios_dpout_match (struct nvkm_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*,struct nvbios_dpout*) ; 
 int nvkm_wraux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_ior*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_dp_train_drive(struct lt_state *lt, bool pc)
{
	struct nvkm_dp *dp = lt->dp;
	struct nvkm_ior *ior = dp->outp.ior;
	struct nvkm_bios *bios = ior->disp->engine.subdev.device->bios;
	struct nvbios_dpout info;
	struct nvbios_dpcfg ocfg;
	u8  ver, hdr, cnt, len;
	u32 data;
	int ret, i;

	for (i = 0; i < ior->dp.nr; i++) {
		u8 lane = (lt->stat[4 + (i >> 1)] >> ((i & 1) * 4)) & 0xf;
		u8 lpc2 = (lt->pc2stat >> (i * 2)) & 0x3;
		u8 lpre = (lane & 0x0c) >> 2;
		u8 lvsw = (lane & 0x03) >> 0;
		u8 hivs = 3 - lpre;
		u8 hipe = 3;
		u8 hipc = 3;

		if (lpc2 >= hipc)
			lpc2 = hipc | DPCD_LC0F_LANE0_MAX_POST_CURSOR2_REACHED;
		if (lpre >= hipe) {
			lpre = hipe | DPCD_LC03_MAX_SWING_REACHED; /* yes. */
			lvsw = hivs = 3 - (lpre & 3);
		} else
		if (lvsw >= hivs) {
			lvsw = hivs | DPCD_LC03_MAX_SWING_REACHED;
		}

		lt->conf[i] = (lpre << 3) | lvsw;
		lt->pc2conf[i >> 1] |= lpc2 << ((i & 1) * 4);

		OUTP_TRACE(&dp->outp, "config lane %d %02x %02x",
			   i, lt->conf[i], lpc2);

		data = nvbios_dpout_match(bios, dp->outp.info.hasht,
						dp->outp.info.hashm,
					  &ver, &hdr, &cnt, &len, &info);
		if (!data)
			continue;

		data = nvbios_dpcfg_match(bios, data, lpc2 & 3, lvsw & 3,
					  lpre & 3, &ver, &hdr, &cnt, &len,
					  &ocfg);
		if (!data)
			continue;

		ior->func->dp.drive(ior, i, ocfg.pc, ocfg.dc,
					    ocfg.pe, ocfg.tx_pu);
	}

	ret = nvkm_wraux(dp->aux, DPCD_LC03(0), lt->conf, 4);
	if (ret)
		return ret;

	if (pc) {
		ret = nvkm_wraux(dp->aux, DPCD_LC0F, lt->pc2conf, 2);
		if (ret)
			return ret;
	}

	return 0;
}