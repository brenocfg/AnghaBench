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
typedef  size_t u32 ;
struct nvkm_bios {int* data; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_addr (struct nvkm_bios*,size_t*,int) ; 

u8
nvbios_rd08(struct nvkm_bios *bios, u32 addr)
{
	if (likely(nvbios_addr(bios, &addr, 1)))
		return bios->data[addr];
	return 0x00;
}