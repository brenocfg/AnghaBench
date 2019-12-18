#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mvumi_hw_regs {int /*<<< orphan*/  arm_to_pciea_msg1; int /*<<< orphan*/  pciea_to_arm_drbl_reg; int /*<<< orphan*/  enpointa_mask_reg; } ;
struct mvumi_hba {TYPE_1__* pdev; struct mvumi_hw_regs* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBL_MU_RESET ; 
 int FAILED ; 
 unsigned long FW_MAX_DELAY ; 
 scalar_t__ HANDSHAKE_READYSTATE ; 
 unsigned long HZ ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int mvumi_wait_for_fw(struct mvumi_hba *mhba)
{
	struct mvumi_hw_regs *regs = mhba->regs;
	u32 tmp;
	unsigned long before;
	before = jiffies;

	iowrite32(0, regs->enpointa_mask_reg);
	tmp = ioread32(regs->arm_to_pciea_msg1);
	while (tmp != HANDSHAKE_READYSTATE) {
		iowrite32(DRBL_MU_RESET, regs->pciea_to_arm_drbl_reg);
		if (time_after(jiffies, before + FW_MAX_DELAY * HZ)) {
			dev_err(&mhba->pdev->dev,
				"FW reset failed [0x%x].\n", tmp);
			return FAILED;
		}

		msleep(500);
		rmb();
		tmp = ioread32(regs->arm_to_pciea_msg1);
	}

	return SUCCESS;
}