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
struct bnxt_fw_health {int* regs; scalar_t__* mapped_regs; } ;
struct bnxt {scalar_t__ bar0; struct bnxt_fw_health* fw_health; } ;

/* Variables and functions */
 scalar_t__ BNXT_FW_HEALTH_REG_TYPE (int) ; 
 scalar_t__ BNXT_FW_HEALTH_REG_TYPE_GRC ; 
 scalar_t__ BNXT_FW_HEALTH_WIN_BASE ; 
 scalar_t__ BNXT_FW_HEALTH_WIN_MAP_OFF ; 
 scalar_t__ BNXT_GRCPF_REG_WINDOW_BASE_OUT ; 
 int BNXT_GRC_BASE_MASK ; 
 int BNXT_GRC_OFFSET_MASK ; 
 int ERANGE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bnxt_map_fw_health_regs(struct bnxt *bp)
{
	struct bnxt_fw_health *fw_health = bp->fw_health;
	u32 reg_base = 0xffffffff;
	int i;

	/* Only pre-map the monitoring GRC registers using window 3 */
	for (i = 0; i < 4; i++) {
		u32 reg = fw_health->regs[i];

		if (BNXT_FW_HEALTH_REG_TYPE(reg) != BNXT_FW_HEALTH_REG_TYPE_GRC)
			continue;
		if (reg_base == 0xffffffff)
			reg_base = reg & BNXT_GRC_BASE_MASK;
		if ((reg & BNXT_GRC_BASE_MASK) != reg_base)
			return -ERANGE;
		fw_health->mapped_regs[i] = BNXT_FW_HEALTH_WIN_BASE +
					    (reg & BNXT_GRC_OFFSET_MASK);
	}
	if (reg_base == 0xffffffff)
		return 0;

	writel(reg_base, bp->bar0 + BNXT_GRCPF_REG_WINDOW_BASE_OUT +
			 BNXT_FW_HEALTH_WIN_MAP_OFF);
	return 0;
}