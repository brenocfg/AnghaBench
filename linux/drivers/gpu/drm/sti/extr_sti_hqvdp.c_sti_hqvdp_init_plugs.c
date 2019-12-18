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
struct sti_hqvdp {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HQVDP_RD_PLUG_CONTROL ; 
 scalar_t__ HQVDP_RD_PLUG_MAX_CHK ; 
 scalar_t__ HQVDP_RD_PLUG_MAX_MSG ; 
 scalar_t__ HQVDP_RD_PLUG_MAX_OPC ; 
 scalar_t__ HQVDP_RD_PLUG_MIN_OPC ; 
 scalar_t__ HQVDP_RD_PLUG_MIN_SPACE ; 
 scalar_t__ HQVDP_RD_PLUG_PAGE_SIZE ; 
 scalar_t__ HQVDP_WR_PLUG_CONTROL ; 
 scalar_t__ HQVDP_WR_PLUG_MAX_CHK ; 
 scalar_t__ HQVDP_WR_PLUG_MAX_MSG ; 
 scalar_t__ HQVDP_WR_PLUG_MAX_OPC ; 
 scalar_t__ HQVDP_WR_PLUG_MIN_OPC ; 
 scalar_t__ HQVDP_WR_PLUG_MIN_SPACE ; 
 scalar_t__ HQVDP_WR_PLUG_PAGE_SIZE ; 
 int /*<<< orphan*/  PLUG_CONTROL_ENABLE ; 
 int /*<<< orphan*/  PLUG_MAX_CHK_2X ; 
 int /*<<< orphan*/  PLUG_MAX_MSG_1X ; 
 int /*<<< orphan*/  PLUG_MAX_OPC_64 ; 
 int /*<<< orphan*/  PLUG_MIN_OPC_8 ; 
 int /*<<< orphan*/  PLUG_MIN_SPACE_1 ; 
 int /*<<< orphan*/  PLUG_PAGE_SIZE_256 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sti_hqvdp_init_plugs(struct sti_hqvdp *hqvdp)
{
	/* Configure Plugs (same for RD & WR) */
	writel(PLUG_PAGE_SIZE_256, hqvdp->regs + HQVDP_RD_PLUG_PAGE_SIZE);
	writel(PLUG_MIN_OPC_8, hqvdp->regs + HQVDP_RD_PLUG_MIN_OPC);
	writel(PLUG_MAX_OPC_64, hqvdp->regs + HQVDP_RD_PLUG_MAX_OPC);
	writel(PLUG_MAX_CHK_2X, hqvdp->regs + HQVDP_RD_PLUG_MAX_CHK);
	writel(PLUG_MAX_MSG_1X, hqvdp->regs + HQVDP_RD_PLUG_MAX_MSG);
	writel(PLUG_MIN_SPACE_1, hqvdp->regs + HQVDP_RD_PLUG_MIN_SPACE);
	writel(PLUG_CONTROL_ENABLE, hqvdp->regs + HQVDP_RD_PLUG_CONTROL);

	writel(PLUG_PAGE_SIZE_256, hqvdp->regs + HQVDP_WR_PLUG_PAGE_SIZE);
	writel(PLUG_MIN_OPC_8, hqvdp->regs + HQVDP_WR_PLUG_MIN_OPC);
	writel(PLUG_MAX_OPC_64, hqvdp->regs + HQVDP_WR_PLUG_MAX_OPC);
	writel(PLUG_MAX_CHK_2X, hqvdp->regs + HQVDP_WR_PLUG_MAX_CHK);
	writel(PLUG_MAX_MSG_1X, hqvdp->regs + HQVDP_WR_PLUG_MAX_MSG);
	writel(PLUG_MIN_SPACE_1, hqvdp->regs + HQVDP_WR_PLUG_MIN_SPACE);
	writel(PLUG_CONTROL_ENABLE, hqvdp->regs + HQVDP_WR_PLUG_CONTROL);
}