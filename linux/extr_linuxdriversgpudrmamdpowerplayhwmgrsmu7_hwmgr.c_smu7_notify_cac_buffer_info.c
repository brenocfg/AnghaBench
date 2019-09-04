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
struct smu7_hwmgr {scalar_t__ soft_regs_start; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  DRAM_LOG_ADDR_H ; 
 int /*<<< orphan*/  DRAM_LOG_ADDR_L ; 
 int /*<<< orphan*/  DRAM_LOG_BUFF_SIZE ; 
 int /*<<< orphan*/  DRAM_LOG_PHY_ADDR_H ; 
 int /*<<< orphan*/  DRAM_LOG_PHY_ADDR_L ; 
 int /*<<< orphan*/  SMU_SoftRegisters ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ smum_get_offsetof (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_notify_cac_buffer_info(struct pp_hwmgr *hwmgr,
					uint32_t virtual_addr_low,
					uint32_t virtual_addr_hi,
					uint32_t mc_addr_low,
					uint32_t mc_addr_hi,
					uint32_t size)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_ADDR_H),
					mc_addr_hi);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_ADDR_L),
					mc_addr_low);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_PHY_ADDR_H),
					virtual_addr_hi);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_PHY_ADDR_L),
					virtual_addr_low);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_BUFF_SIZE),
					size);
	return 0;
}