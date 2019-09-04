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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_cstepE {int pstate; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_cstepE*,int,int) ; 
 scalar_t__ nvbios_cstepEe (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_cstepEp(struct nvkm_bios *bios, int idx, u8 *ver, u8 *hdr,
	       struct nvbios_cstepE *info)
{
	u32 data = nvbios_cstepEe(bios, idx, ver, hdr);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->pstate = (nvbios_rd16(bios, data + 0x00) & 0x01e0) >> 5;
		info->index   = nvbios_rd08(bios, data + 0x03);
	}
	return data;
}