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
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 unsigned char nvbios_rd08 (struct nvkm_bios*,int /*<<< orphan*/ ) ; 

int
nvbios_memcmp(struct nvkm_bios *bios, u32 addr, const char *str, u32 len)
{
	unsigned char c1, c2;

	while (len--) {
		c1 = nvbios_rd08(bios, addr++);
		c2 = *(str++);
		if (c1 != c2)
			return c1 - c2;
	}
	return 0;
}