#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_clk {TYPE_2__ subdev; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_boostS {scalar_t__ domain; int percent; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct nvbios_boostE {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int nvbios_boostEm (struct nvkm_bios*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,struct nvbios_boostE*) ; 
 int nvbios_boostSp (struct nvkm_bios*,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*,scalar_t__,scalar_t__,struct nvbios_boostS*) ; 

__attribute__((used)) static u32
nvkm_clk_adjust(struct nvkm_clk *clk, bool adjust,
		u8 pstate, u8 domain, u32 input)
{
	struct nvkm_bios *bios = clk->subdev.device->bios;
	struct nvbios_boostE boostE;
	u8  ver, hdr, cnt, len;
	u32 data;

	data = nvbios_boostEm(bios, pstate, &ver, &hdr, &cnt, &len, &boostE);
	if (data) {
		struct nvbios_boostS boostS;
		u8  idx = 0, sver, shdr;
		u32 subd;

		input = max(boostE.min, input);
		input = min(boostE.max, input);
		do {
			sver = ver;
			shdr = hdr;
			subd = nvbios_boostSp(bios, idx++, data, &sver, &shdr,
					      cnt, len, &boostS);
			if (subd && boostS.domain == domain) {
				if (adjust)
					input = input * boostS.percent / 100;
				input = max(boostS.min, input);
				input = min(boostS.max, input);
				break;
			}
		} while (subd);
	}

	return input;
}