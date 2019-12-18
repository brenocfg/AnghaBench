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
struct efx_nic {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int efx_ef10_pf_mem_bar(struct efx_nic *efx)
{
	switch (efx->pci_dev->device) {
	case 0x0b03: /* SFC9250 PF */
		return 0;
	default:
		return 2;
	}
}