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
struct TYPE_3__ {int timing_ver; int timing_10_CWL; int timing_10_CL; int timing_10_WR; int timing_10_ODT; int ramcfg_RON; int* timing; int ramcfg_timing; int /*<<< orphan*/  ramcfg_DLLoff; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  ramgddr3_cl_hi ; 
 int /*<<< orphan*/  ramgddr3_cl_lo ; 
 int /*<<< orphan*/  ramgddr3_wr_lo ; 
 int ramxlat (int /*<<< orphan*/ ,int) ; 

int
nvkm_gddr3_calc(struct nvkm_ram *ram)
{
	int CL, WR, CWL, DLL = 0, ODT = 0, RON, hi;

	switch (ram->next->bios.timing_ver) {
	case 0x10:
		CWL = ram->next->bios.timing_10_CWL;
		CL  = ram->next->bios.timing_10_CL;
		WR  = ram->next->bios.timing_10_WR;
		DLL = !ram->next->bios.ramcfg_DLLoff;
		ODT = ram->next->bios.timing_10_ODT;
		RON = ram->next->bios.ramcfg_RON;
		break;
	case 0x20:
		CWL = (ram->next->bios.timing[1] & 0x00000f80) >> 7;
		CL  = (ram->next->bios.timing[1] & 0x0000001f) >> 0;
		WR  = (ram->next->bios.timing[2] & 0x007f0000) >> 16;
		/* XXX: Get these values from the VBIOS instead */
		DLL = !(ram->mr[1] & 0x1);
		RON = !((ram->mr[1] & 0x300) >> 8);
		break;
	default:
		return -ENOSYS;
	}

	if (ram->next->bios.timing_ver == 0x20 ||
	    ram->next->bios.ramcfg_timing == 0xff) {
		ODT =  (ram->mr[1] & 0xc) >> 2;
	}

	hi = ram->mr[2] & 0x1;
	CL  = ramxlat(hi ? ramgddr3_cl_hi : ramgddr3_cl_lo, CL);
	WR  = ramxlat(ramgddr3_wr_lo, WR);
	if (CL < 0 || CWL < 1 || CWL > 7 || WR < 0)
		return -EINVAL;

	ram->mr[0] &= ~0xf74;
	ram->mr[0] |= (CWL & 0x07) << 9;
	ram->mr[0] |= (CL & 0x07) << 4;
	ram->mr[0] |= (CL & 0x08) >> 1;

	ram->mr[1] &= ~0x3fc;
	ram->mr[1] |= (ODT & 0x03) << 2;
	ram->mr[1] |= (RON & 0x03) << 8;
	ram->mr[1] |= (WR  & 0x03) << 4;
	ram->mr[1] |= (WR  & 0x04) << 5;
	ram->mr[1] |= !DLL << 6;
	return 0;
}