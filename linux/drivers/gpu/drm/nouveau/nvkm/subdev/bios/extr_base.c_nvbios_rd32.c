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
typedef  size_t u32 ;
struct nvkm_bios {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_addr (struct nvkm_bios*,size_t*,int) ; 

u32
nvbios_rd32(struct nvkm_bios *bios, u32 addr)
{
	if (likely(nvbios_addr(bios, &addr, 4)))
		return get_unaligned_le32(&bios->data[addr]);
	return 0x00000000;
}