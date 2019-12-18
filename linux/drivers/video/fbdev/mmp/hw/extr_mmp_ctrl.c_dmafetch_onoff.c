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
typedef  int /*<<< orphan*/  u32 ;
struct mmp_path {int /*<<< orphan*/  id; } ;
struct mmp_overlay {int /*<<< orphan*/  access_ok; struct mmp_path* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_DMA_ENA (int) ; 
 int /*<<< orphan*/  CFG_DMA_ENA_MASK ; 
 int /*<<< orphan*/  CFG_GRA_ENA (int) ; 
 int /*<<< orphan*/  CFG_GRA_ENA_MASK ; 
 scalar_t__ ctrl_regs (struct mmp_path*) ; 
 scalar_t__ dma_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ overlay_is_vid (struct mmp_overlay*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dmafetch_onoff(struct mmp_overlay *overlay, int on)
{
	u32 mask = overlay_is_vid(overlay) ? CFG_DMA_ENA_MASK :
		   CFG_GRA_ENA_MASK;
	u32 enable = overlay_is_vid(overlay) ? CFG_DMA_ENA(1) : CFG_GRA_ENA(1);
	u32 tmp;
	struct mmp_path *path = overlay->path;

	mutex_lock(&overlay->access_ok);
	tmp = readl_relaxed(ctrl_regs(path) + dma_ctrl(0, path->id));
	tmp &= ~mask;
	tmp |= (on ? enable : 0);
	writel(tmp, ctrl_regs(path) + dma_ctrl(0, path->id));
	mutex_unlock(&overlay->access_ok);
}