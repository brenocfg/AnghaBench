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
struct nvkm_ram {int freq; int* mr; int mr1_nuts; TYPE_2__* next; } ;
struct TYPE_3__ {int ramcfg_ver; int ramcfg_11_01_80; int ramcfg_11_01_40; int ramcfg_11_02_10; int ramcfg_11_02_04; int ramcfg_11_06; int timing_ver; int* timing; int timing_20_2e_c0; int timing_20_2e_30; int timing_20_2e_03; int timing_20_2f_03; int /*<<< orphan*/  ramcfg_11_07_02; int /*<<< orphan*/  ramcfg_DLLoff; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ NOTE00 (int) ; 

int
nvkm_gddr5_calc(struct nvkm_ram *ram, bool nuts)
{
	int pd, lf, xd, vh, vr, vo, l3;
	int WL, CL, WR, at[2], dt, ds;
	int rq = ram->freq < 1000000; /* XXX */

	xd = !ram->next->bios.ramcfg_DLLoff;

	switch (ram->next->bios.ramcfg_ver) {
	case 0x11:
		pd =  ram->next->bios.ramcfg_11_01_80;
		lf =  ram->next->bios.ramcfg_11_01_40;
		vh =  ram->next->bios.ramcfg_11_02_10;
		vr =  ram->next->bios.ramcfg_11_02_04;
		vo =  ram->next->bios.ramcfg_11_06;
		l3 = !ram->next->bios.ramcfg_11_07_02;
		break;
	default:
		return -ENOSYS;
	}

	switch (ram->next->bios.timing_ver) {
	case 0x20:
		WL = (ram->next->bios.timing[1] & 0x00000f80) >> 7;
		CL = (ram->next->bios.timing[1] & 0x0000001f);
		WR = (ram->next->bios.timing[2] & 0x007f0000) >> 16;
		at[0] = ram->next->bios.timing_20_2e_c0;
		at[1] = ram->next->bios.timing_20_2e_30;
		dt =  ram->next->bios.timing_20_2e_03;
		ds =  ram->next->bios.timing_20_2f_03;
		break;
	default:
		return -ENOSYS;
	}

	if (WL < 1 || WL > 7 || CL < 5 || CL > 36 || WR < 4 || WR > 35)
		return -EINVAL;
	CL -= 5;
	WR -= 4;

	ram->mr[0] &= ~0xf7f;
	ram->mr[0] |= (WR & 0x0f) << 8;
	ram->mr[0] |= (CL & 0x0f) << 3;
	ram->mr[0] |= (WL & 0x07) << 0;

	ram->mr[1] &= ~0x0bf;
	ram->mr[1] |= (xd & 0x01) << 7;
	ram->mr[1] |= (at[0] & 0x03) << 4;
	ram->mr[1] |= (dt & 0x03) << 2;
	ram->mr[1] |= (ds & 0x03) << 0;

	/* this seems wrong, alternate field used for the broadcast
	 * on nuts vs non-nuts configs..  meh, it matches for now.
	 */
	ram->mr1_nuts = ram->mr[1];
	if (nuts) {
		ram->mr[1] &= ~0x030;
		ram->mr[1] |= (at[1] & 0x03) << 4;
	}

	ram->mr[3] &= ~0x020;
	ram->mr[3] |= (rq & 0x01) << 5;

	ram->mr[5] &= ~0x004;
	ram->mr[5] |= (l3 << 2);

	if (!vo)
		vo = (ram->mr[6] & 0xff0) >> 4;
	if (ram->mr[6] & 0x001)
		pd = 1; /* binary driver does this.. bug? */
	ram->mr[6] &= ~0xff1;
	ram->mr[6] |= (vo & 0xff) << 4;
	ram->mr[6] |= (pd & 0x01) << 0;

	if (NOTE00(vr)) {
		ram->mr[7] &= ~0x300;
		ram->mr[7] |= (vr & 0x03) << 8;
	}
	ram->mr[7] &= ~0x088;
	ram->mr[7] |= (vh & 0x01) << 7;
	ram->mr[7] |= (lf & 0x01) << 3;

	ram->mr[8] &= ~0x003;
	ram->mr[8] |= (WR & 0x10) >> 3;
	ram->mr[8] |= (CL & 0x10) >> 4;
	return 0;
}