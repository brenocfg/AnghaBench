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
struct stm32_usbphyc {int nphys; TYPE_1__** phys; } ;
struct TYPE_2__ {scalar_t__ active; } ;

/* Variables and functions */

__attribute__((used)) static bool stm32_usbphyc_has_one_phy_active(struct stm32_usbphyc *usbphyc)
{
	int i;

	for (i = 0; i < usbphyc->nphys; i++)
		if (usbphyc->phys[i]->active)
			return true;

	return false;
}