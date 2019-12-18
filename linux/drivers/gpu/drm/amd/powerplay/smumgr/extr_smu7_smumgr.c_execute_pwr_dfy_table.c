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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int dfy_size; int /*<<< orphan*/ * dfy_data; int /*<<< orphan*/  dfy_addr_lo; int /*<<< orphan*/  dfy_addr_hi; int /*<<< orphan*/  dfy_cntl; } ;
typedef  TYPE_1__ PWR_DFY_Section ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_DFY_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_DFY_ADDR_LO ; 
 int /*<<< orphan*/  mmCP_DFY_CNTL ; 
 int /*<<< orphan*/  mmCP_DFY_DATA_0 ; 

__attribute__((used)) static void execute_pwr_dfy_table(struct pp_hwmgr *hwmgr, const PWR_DFY_Section *section)
{
	int i;

	cgs_write_register(hwmgr->device, mmCP_DFY_CNTL, section->dfy_cntl);
	cgs_write_register(hwmgr->device, mmCP_DFY_ADDR_HI, section->dfy_addr_hi);
	cgs_write_register(hwmgr->device, mmCP_DFY_ADDR_LO, section->dfy_addr_lo);
	for (i = 0; i < section->dfy_size; i++)
		cgs_write_register(hwmgr->device, mmCP_DFY_DATA_0, section->dfy_data[i]);
}