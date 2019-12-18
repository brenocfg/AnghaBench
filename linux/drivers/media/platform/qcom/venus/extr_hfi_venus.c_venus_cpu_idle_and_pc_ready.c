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
typedef  int u32 ;
struct venus_hfi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CS_SCIACMDARG0 ; 
 int CPU_CS_SCIACMDARG0_PC_READY ; 
 int /*<<< orphan*/  WRAPPER_CPU_STATUS ; 
 int WRAPPER_CPU_STATUS_WFI ; 
 int venus_readl (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool venus_cpu_idle_and_pc_ready(struct venus_hfi_device *hdev)
{
	u32 ctrl_status, cpu_status;

	cpu_status = venus_readl(hdev, WRAPPER_CPU_STATUS);
	ctrl_status = venus_readl(hdev, CPU_CS_SCIACMDARG0);

	if (cpu_status & WRAPPER_CPU_STATUS_WFI &&
	    ctrl_status & CPU_CS_SCIACMDARG0_PC_READY)
		return true;

	return false;
}