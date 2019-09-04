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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_mc_info; } ;
struct sbridge_pvt {TYPE_1__ knl; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNL_TOHM_0 ; 
 int /*<<< orphan*/  KNL_TOHM_1 ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u64 knl_get_tohm(struct sbridge_pvt *pvt)
{
	u64 rc;
	u32 reg_lo, reg_hi;

	pci_read_config_dword(pvt->knl.pci_mc_info, KNL_TOHM_0, &reg_lo);
	pci_read_config_dword(pvt->knl.pci_mc_info, KNL_TOHM_1, &reg_hi);
	rc = ((u64)reg_hi << 32) | reg_lo;
	return rc | 0x3ffffff;
}