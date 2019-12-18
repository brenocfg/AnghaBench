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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int TPC0_CFG_TPC_STALL_V_SHIFT ; 
 int TPC1_CFG_TPC_STALL_V_SHIFT ; 
 int TPC2_CFG_TPC_STALL_V_SHIFT ; 
 int TPC3_CFG_TPC_STALL_V_SHIFT ; 
 int TPC4_CFG_TPC_STALL_V_SHIFT ; 
 int TPC5_CFG_TPC_STALL_V_SHIFT ; 
 int TPC6_CFG_TPC_STALL_V_SHIFT ; 
 int TPC7_CFG_TPC_STALL_V_SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmTPC0_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC1_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC2_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC3_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC4_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC5_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC6_CFG_TPC_STALL ; 
 int /*<<< orphan*/  mmTPC7_CFG_TPC_STALL ; 

__attribute__((used)) static void goya_tpc_stall(struct hl_device *hdev)
{
	WREG32(mmTPC0_CFG_TPC_STALL, 1 << TPC0_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC1_CFG_TPC_STALL, 1 << TPC1_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC2_CFG_TPC_STALL, 1 << TPC2_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC3_CFG_TPC_STALL, 1 << TPC3_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC4_CFG_TPC_STALL, 1 << TPC4_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC5_CFG_TPC_STALL, 1 << TPC5_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC6_CFG_TPC_STALL, 1 << TPC6_CFG_TPC_STALL_V_SHIFT);
	WREG32(mmTPC7_CFG_TPC_STALL, 1 << TPC7_CFG_TPC_STALL_V_SHIFT);
}