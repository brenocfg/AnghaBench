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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_cstepE {scalar_t__ pstate; } ;

/* Variables and functions */
 scalar_t__ nvbios_cstepEp (struct nvkm_bios*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,struct nvbios_cstepE*) ; 

u32
nvbios_cstepEm(struct nvkm_bios *bios, u8 pstate, u8 *ver, u8 *hdr,
	       struct nvbios_cstepE *info)
{
	u32 data, idx = 0;
	while ((data = nvbios_cstepEp(bios, idx++, ver, hdr, info))) {
		if (info->pstate == pstate)
			break;
	}
	return data;
}