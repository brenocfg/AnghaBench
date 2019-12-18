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
typedef  scalar_t__ uint32_t ;
struct smu7_hwmgr {scalar_t__ soft_regs_start; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  HandshakeDisables ; 
 scalar_t__ SMU7_VCE_SCLK_HANDSHAKE_DISABLE ; 
 int /*<<< orphan*/  SMU_SoftRegisters ; 
 scalar_t__ cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ smum_get_offsetof (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_disable_sclk_vce_handshake(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	uint32_t soft_register_value = 0;
	uint32_t handshake_disables_offset = data->soft_regs_start
				+ smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, HandshakeDisables);

	soft_register_value = cgs_read_ind_register(hwmgr->device,
				CGS_IND_REG__SMC, handshake_disables_offset);
	soft_register_value |= SMU7_VCE_SCLK_HANDSHAKE_DISABLE;
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
			handshake_disables_offset, soft_register_value);
	return 0;
}