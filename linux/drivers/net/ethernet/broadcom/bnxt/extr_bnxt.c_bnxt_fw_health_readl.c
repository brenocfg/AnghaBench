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
struct bnxt_fw_health {int* regs; int* mapped_regs; int fw_reset_inprog_reg_mask; } ;
struct bnxt {int bar0; int bar1; int /*<<< orphan*/  pdev; struct bnxt_fw_health* fw_health; } ;

/* Variables and functions */
 int BNXT_FW_HEALTH_REG_OFF (int) ; 
 int BNXT_FW_HEALTH_REG_TYPE (int) ; 
#define  BNXT_FW_HEALTH_REG_TYPE_BAR0 131 
#define  BNXT_FW_HEALTH_REG_TYPE_BAR1 130 
#define  BNXT_FW_HEALTH_REG_TYPE_CFG 129 
#define  BNXT_FW_HEALTH_REG_TYPE_GRC 128 
 int BNXT_FW_RESET_INPROG_REG ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int readl (int) ; 

u32 bnxt_fw_health_readl(struct bnxt *bp, int reg_idx)
{
	struct bnxt_fw_health *fw_health = bp->fw_health;
	u32 reg = fw_health->regs[reg_idx];
	u32 reg_type, reg_off, val = 0;

	reg_type = BNXT_FW_HEALTH_REG_TYPE(reg);
	reg_off = BNXT_FW_HEALTH_REG_OFF(reg);
	switch (reg_type) {
	case BNXT_FW_HEALTH_REG_TYPE_CFG:
		pci_read_config_dword(bp->pdev, reg_off, &val);
		break;
	case BNXT_FW_HEALTH_REG_TYPE_GRC:
		reg_off = fw_health->mapped_regs[reg_idx];
		/* fall through */
	case BNXT_FW_HEALTH_REG_TYPE_BAR0:
		val = readl(bp->bar0 + reg_off);
		break;
	case BNXT_FW_HEALTH_REG_TYPE_BAR1:
		val = readl(bp->bar1 + reg_off);
		break;
	}
	if (reg_idx == BNXT_FW_RESET_INPROG_REG)
		val &= fw_health->fw_reset_inprog_reg_mask;
	return val;
}