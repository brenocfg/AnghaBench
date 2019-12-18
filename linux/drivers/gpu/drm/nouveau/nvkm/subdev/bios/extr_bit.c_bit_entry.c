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
struct nvkm_bios {scalar_t__ bit_offset; } ;
struct bit_entry {void* offset; void* length; scalar_t__ version; scalar_t__ id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ likely (scalar_t__) ; 
 scalar_t__ nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 void* nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

int
bit_entry(struct nvkm_bios *bios, u8 id, struct bit_entry *bit)
{
	if (likely(bios->bit_offset)) {
		u8  entries = nvbios_rd08(bios, bios->bit_offset + 10);
		u32 entry   = bios->bit_offset + 12;
		while (entries--) {
			if (nvbios_rd08(bios, entry + 0) == id) {
				bit->id      = nvbios_rd08(bios, entry + 0);
				bit->version = nvbios_rd08(bios, entry + 1);
				bit->length  = nvbios_rd16(bios, entry + 2);
				bit->offset  = nvbios_rd16(bios, entry + 4);
				return 0;
			}

			entry += nvbios_rd08(bios, bios->bit_offset + 9);
		}

		return -ENOENT;
	}

	return -EINVAL;
}