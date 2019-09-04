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
typedef  int u16 ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 int init_table (struct nvkm_bios*,int*) ; 
 int nvbios_rd16 (struct nvkm_bios*,int) ; 

__attribute__((used)) static u16
init_unknown_script(struct nvkm_bios *bios)
{
	u16 len, data = init_table(bios, &len);
	if (data && len >= 16)
		return nvbios_rd16(bios, data + 14);
	return 0x0000;
}