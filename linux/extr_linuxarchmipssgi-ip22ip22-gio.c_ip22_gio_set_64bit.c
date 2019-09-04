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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  giopar; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGIMC_GIOPAR_EXP064 ; 
 int /*<<< orphan*/  SGIMC_GIOPAR_EXP164 ; 
 int /*<<< orphan*/  SGIMC_GIOPAR_GFX64 ; 
 TYPE_1__* sgimc ; 

void ip22_gio_set_64bit(int slotno)
{
	u32 tmp = sgimc->giopar;

	switch (slotno) {
	case 0:
		tmp |= SGIMC_GIOPAR_GFX64;
		break;
	case 1:
		tmp |= SGIMC_GIOPAR_EXP064;
		break;
	case 2:
		tmp |= SGIMC_GIOPAR_EXP164;
		break;
	}
	sgimc->giopar = tmp;
}