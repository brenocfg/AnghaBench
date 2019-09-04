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
typedef  int u32 ;
struct nvkm_bios {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int nouveau_acpi_get_bios_chunk (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ nvbios_extend (struct nvkm_bios*,int) ; 

__attribute__((used)) static u32
acpi_read_slow(void *data, u32 offset, u32 length, struct nvkm_bios *bios)
{
	u32 limit = (offset + length + 0xfff) & ~0xfff;
	u32 start = offset & ~0xfff;
	u32 fetch = 0;

	if (nvbios_extend(bios, limit) >= 0) {
		while (start + fetch < limit) {
			int ret = nouveau_acpi_get_bios_chunk(bios->data,
							      start + fetch,
							      0x1000);
			if (ret != 0x1000)
				break;
			fetch += 0x1000;
		}
	}

	return fetch;
}