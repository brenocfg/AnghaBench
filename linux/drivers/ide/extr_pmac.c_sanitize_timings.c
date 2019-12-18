#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int kind; unsigned int* timings; } ;
typedef  TYPE_1__ pmac_ide_hwif_t ;

/* Variables and functions */
#define  controller_heathrow 134 
#define  controller_k2_ata6 133 
#define  controller_kl_ata3 132 
#define  controller_kl_ata4 131 
#define  controller_ohare 130 
#define  controller_sh_ata6 129 
#define  controller_un_ata6 128 

__attribute__((used)) static void
sanitize_timings(pmac_ide_hwif_t *pmif)
{
	unsigned int value, value2 = 0;
	
	switch(pmif->kind) {
		case controller_sh_ata6:
			value = 0x0a820c97;
			value2 = 0x00033031;
			break;
		case controller_un_ata6:
		case controller_k2_ata6:
			value = 0x08618a92;
			value2 = 0x00002921;
			break;
		case controller_kl_ata4:
			value = 0x0008438c;
			break;
		case controller_kl_ata3:
			value = 0x00084526;
			break;
		case controller_heathrow:
		case controller_ohare:
		default:
			value = 0x00074526;
			break;
	}
	pmif->timings[0] = pmif->timings[1] = value;
	pmif->timings[2] = pmif->timings[3] = value2;
}