#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  PRAMDAC0; } ;
struct riva_par {int FlatPanel; int Chipset; void* SecondCRTC; TYPE_1__ riva; } ;

/* Variables and functions */
 void* FALSE ; 
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 
 void* TRUE ; 
 scalar_t__ riva_is_connected (struct riva_par*,int) ; 
 int /*<<< orphan*/  riva_override_CRTC (struct riva_par*) ; 

__attribute__((used)) static void
riva_is_second(struct riva_par *par)
{
	if (par->FlatPanel == 1) {
		switch(par->Chipset & 0xffff) {
		case 0x0174:
		case 0x0175:
		case 0x0176:
		case 0x0177:
		case 0x0179:
		case 0x017C:
		case 0x017D:
		case 0x0186:
		case 0x0187:
		/* this might not be a good default for the chips below */
		case 0x0286:
		case 0x028C:
		case 0x0316:
		case 0x0317:
		case 0x031A:
		case 0x031B:
		case 0x031C:
		case 0x031D:
		case 0x031E:
		case 0x031F:
		case 0x0324:
		case 0x0325:
		case 0x0328:
		case 0x0329:
		case 0x032C:
		case 0x032D:
			par->SecondCRTC = TRUE;
			break;
		default:
			par->SecondCRTC = FALSE;
			break;
		}
	} else {
		if(riva_is_connected(par, 0)) {

			if (NV_RD32(par->riva.PRAMDAC0, 0x0000052C) & 0x100)
				par->SecondCRTC = TRUE;
			else
				par->SecondCRTC = FALSE;
		} else 
		if (riva_is_connected(par, 1)) {
			if(NV_RD32(par->riva.PRAMDAC0, 0x0000252C) & 0x100)
				par->SecondCRTC = TRUE;
			else
				par->SecondCRTC = FALSE;
		} else /* default */
			par->SecondCRTC = FALSE;
	}
	riva_override_CRTC(par);
}