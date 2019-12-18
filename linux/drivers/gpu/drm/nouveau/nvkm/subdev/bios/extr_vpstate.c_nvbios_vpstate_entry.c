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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_vpstate_header {int ecount; int elen; int slen; int scount; scalar_t__ hlen; scalar_t__ offset; } ;
struct nvbios_vpstate_entry {int /*<<< orphan*/  clock_mhz; int /*<<< orphan*/  pstate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

int
nvbios_vpstate_entry(struct nvkm_bios *b, struct nvbios_vpstate_header *h,
		     u8 idx, struct nvbios_vpstate_entry *e)
{
	u32 offset;

	if (!e || !h || idx > h->ecount)
		return -EINVAL;

	offset = h->offset + h->hlen + idx * (h->elen + (h->slen * h->scount));
	e->pstate    = nvbios_rd08(b, offset);
	e->clock_mhz = nvbios_rd16(b, offset + 0x5);
	return 0;
}