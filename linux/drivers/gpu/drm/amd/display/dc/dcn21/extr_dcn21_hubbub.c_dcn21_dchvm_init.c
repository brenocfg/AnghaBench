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
struct hubbub {int dummy; } ;
struct dcn20_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHVM_CLK_CTRL ; 
 int /*<<< orphan*/  DCHVM_CTRL0 ; 
 int /*<<< orphan*/  DCHVM_RIOMMU_CTRL0 ; 
 int /*<<< orphan*/  DCHVM_RIOMMU_STAT0 ; 
 int /*<<< orphan*/  HOSTVM_INIT_REQ ; 
 int /*<<< orphan*/  HOSTVM_POWERSTATUS ; 
 int /*<<< orphan*/  HOSTVM_PREFETCH_DONE ; 
 int /*<<< orphan*/  HOSTVM_PREFETCH_REQ ; 
 int /*<<< orphan*/  HVM_DCFCLK_G_GATE_DIS ; 
 int /*<<< orphan*/  HVM_DCFCLK_R_GATE_DIS ; 
 int /*<<< orphan*/  HVM_DISPCLK_G_GATE_DIS ; 
 int /*<<< orphan*/  HVM_DISPCLK_R_GATE_DIS ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  RIOMMU_ACTIVE ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 

void dcn21_dchvm_init(struct hubbub *hubbub)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	//Init DCHVM block
	REG_UPDATE(DCHVM_CTRL0, HOSTVM_INIT_REQ, 1);

	//Poll until RIOMMU_ACTIVE = 1
	//TODO: Figure out interval us and retry count
	REG_WAIT(DCHVM_RIOMMU_STAT0, RIOMMU_ACTIVE, 1, 5, 100);

	//Reflect the power status of DCHUBBUB
	REG_UPDATE(DCHVM_RIOMMU_CTRL0, HOSTVM_POWERSTATUS, 1);

	//Start rIOMMU prefetching
	REG_UPDATE(DCHVM_RIOMMU_CTRL0, HOSTVM_PREFETCH_REQ, 1);

	// Enable dynamic clock gating
	REG_UPDATE_4(DCHVM_CLK_CTRL,
					HVM_DISPCLK_R_GATE_DIS, 0,
					HVM_DISPCLK_G_GATE_DIS, 0,
					HVM_DCFCLK_R_GATE_DIS, 0,
					HVM_DCFCLK_G_GATE_DIS, 0);

	//Poll until HOSTVM_PREFETCH_DONE = 1
	//TODO: Figure out interval us and retry count
	REG_WAIT(DCHVM_RIOMMU_STAT0, HOSTVM_PREFETCH_DONE, 1, 5, 100);
}