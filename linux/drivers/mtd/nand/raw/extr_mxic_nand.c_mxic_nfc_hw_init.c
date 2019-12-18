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
struct mxic_nand_ctlr {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HC_CFG ; 
 int HC_CFG_IDLE_SIO_LVL (int) ; 
 int HC_CFG_MAN_CS_EN ; 
 int HC_CFG_NIO (int) ; 
 int HC_CFG_SLV_ACT (int /*<<< orphan*/ ) ; 
 int HC_CFG_TYPE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HC_CFG_TYPE_RAW_NAND ; 
 scalar_t__ HC_EN ; 
 int INT_RDY_PIN ; 
 scalar_t__ INT_SIG_EN ; 
 int INT_STS_ALL ; 
 scalar_t__ INT_STS_EN ; 
 scalar_t__ LRD_CFG ; 
 scalar_t__ LRD_CTRL ; 
 scalar_t__ ONFI_DIN_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxic_nfc_hw_init(struct mxic_nand_ctlr *nfc)
{
	writel(HC_CFG_NIO(8) | HC_CFG_TYPE(1, HC_CFG_TYPE_RAW_NAND) |
	       HC_CFG_SLV_ACT(0) | HC_CFG_MAN_CS_EN |
	       HC_CFG_IDLE_SIO_LVL(1), nfc->regs + HC_CFG);
	writel(INT_STS_ALL, nfc->regs + INT_STS_EN);
	writel(INT_RDY_PIN, nfc->regs + INT_SIG_EN);
	writel(0x0, nfc->regs + ONFI_DIN_CNT(0));
	writel(0, nfc->regs + LRD_CFG);
	writel(0, nfc->regs + LRD_CTRL);
	writel(0x0, nfc->regs + HC_EN);
}