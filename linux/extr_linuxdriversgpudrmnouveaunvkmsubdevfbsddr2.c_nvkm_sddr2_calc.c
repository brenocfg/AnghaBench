#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_ram {int* mr; TYPE_2__* next; } ;
struct TYPE_3__ {int timing_ver; int timing_10_CL; int timing_10_WR; int timing_10_ODT; int* timing; int ramcfg_timing; int /*<<< orphan*/  ramcfg_DLLoff; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  ramddr2_cl ; 
 int /*<<< orphan*/  ramddr2_wr ; 
 int ramxlat (int /*<<< orphan*/ ,int) ; 

int
nvkm_sddr2_calc(struct nvkm_ram *ram)
{
	int CL, WR, DLL = 0, ODT = 0;

	switch (ram->next->bios.timing_ver) {
	case 0x10:
		CL  = ram->next->bios.timing_10_CL;
		WR  = ram->next->bios.timing_10_WR;
		DLL = !ram->next->bios.ramcfg_DLLoff;
		ODT = ram->next->bios.timing_10_ODT & 3;
		break;
	case 0x20:
		CL  = (ram->next->bios.timing[1] & 0x0000001f);
		WR  = (ram->next->bios.timing[2] & 0x007f0000) >> 16;
		break;
	default:
		return -ENOSYS;
	}

	if (ram->next->bios.timing_ver == 0x20 ||
	    ram->next->bios.ramcfg_timing == 0xff) {
		ODT =  (ram->mr[1] & 0x004) >> 2 |
		       (ram->mr[1] & 0x040) >> 5;
	}

	CL  = ramxlat(ramddr2_cl, CL);
	WR  = ramxlat(ramddr2_wr, WR);
	if (CL < 0 || WR < 0)
		return -EINVAL;

	ram->mr[0] &= ~0xf70;
	ram->mr[0] |= (WR & 0x07) << 9;
	ram->mr[0] |= (CL & 0x07) << 4;

	ram->mr[1] &= ~0x045;
	ram->mr[1] |= (ODT & 0x1) << 2;
	ram->mr[1] |= (ODT & 0x2) << 5;
	ram->mr[1] |= !DLL;
	return 0;
}