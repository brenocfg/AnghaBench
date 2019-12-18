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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_DramAddrHiPhysical ; 
 int /*<<< orphan*/  PPSMC_MSG_DramAddrHiVirtual ; 
 int /*<<< orphan*/  PPSMC_MSG_DramAddrLoPhysical ; 
 int /*<<< orphan*/  PPSMC_MSG_DramAddrLoVirtual ; 
 int /*<<< orphan*/  PPSMC_MSG_DramBufferSize ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_notify_cac_buffer_info(struct pp_hwmgr *hwmgr,
					uint32_t virtual_addr_low,
					uint32_t virtual_addr_hi,
					uint32_t mc_addr_low,
					uint32_t mc_addr_hi,
					uint32_t size)
{
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrHiVirtual,
					mc_addr_hi);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrLoVirtual,
					mc_addr_low);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrHiPhysical,
					virtual_addr_hi);
	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramAddrLoPhysical,
					virtual_addr_low);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DramBufferSize,
					size);
	return 0;
}