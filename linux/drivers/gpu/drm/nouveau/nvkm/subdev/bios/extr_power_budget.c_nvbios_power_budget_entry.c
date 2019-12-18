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
struct nvbios_power_budget_entry {void* max_w; void* avg_w; void* min_w; } ;
struct nvbios_power_budget {int ecount; int elen; int ver; scalar_t__ hlen; scalar_t__ offset; } ;

/* Variables and functions */
 int EINVAL ; 
 void* nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

int
nvbios_power_budget_entry(struct nvkm_bios *bios,
                          struct nvbios_power_budget *budget,
                          u8 idx, struct nvbios_power_budget_entry *entry)
{
	u32 entry_offset;

	if (!bios || !budget || !budget->offset || idx >= budget->ecount
		|| !entry)
		return -EINVAL;

	entry_offset = budget->offset + budget->hlen + idx * budget->elen;

	if (budget->ver >= 0x20) {
		entry->min_w = nvbios_rd32(bios, entry_offset + 0x2);
		entry->avg_w = nvbios_rd32(bios, entry_offset + 0x6);
		entry->max_w = nvbios_rd32(bios, entry_offset + 0xa);
	} else {
		entry->min_w = 0;
		entry->max_w = nvbios_rd32(bios, entry_offset + 0x2);
		entry->avg_w = entry->max_w;
	}

	return 0;
}