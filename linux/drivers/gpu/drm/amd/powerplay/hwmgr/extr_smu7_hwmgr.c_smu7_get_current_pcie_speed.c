#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__PCIE ; 
 int /*<<< orphan*/  LC_CURRENT_DATA_RATE ; 
 int /*<<< orphan*/  PCIE_LC_SPEED_CNTL ; 
 scalar_t__ PHM_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixPCIE_LC_SPEED_CNTL ; 

__attribute__((used)) static uint16_t smu7_get_current_pcie_speed(struct pp_hwmgr *hwmgr)
{
	uint32_t speedCntl = 0;

	/* mmPCIE_PORT_INDEX rename as mmPCIE_INDEX */
	speedCntl = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__PCIE,
			ixPCIE_LC_SPEED_CNTL);
	return((uint16_t)PHM_GET_FIELD(speedCntl,
			PCIE_LC_SPEED_CNTL, LC_CURRENT_DATA_RATE));
}