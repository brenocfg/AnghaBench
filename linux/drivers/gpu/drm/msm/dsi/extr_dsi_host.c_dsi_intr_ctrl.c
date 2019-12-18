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
struct msm_dsi_host {int /*<<< orphan*/  intr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_DSI_INTR_CTRL ; 
 int /*<<< orphan*/  dsi_read (struct msm_dsi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dsi_intr_ctrl(struct msm_dsi_host *msm_host, u32 mask, int enable)
{
	u32 intr;
	unsigned long flags;

	spin_lock_irqsave(&msm_host->intr_lock, flags);
	intr = dsi_read(msm_host, REG_DSI_INTR_CTRL);

	if (enable)
		intr |= mask;
	else
		intr &= ~mask;

	DBG("intr=%x enable=%d", intr, enable);

	dsi_write(msm_host, REG_DSI_INTR_CTRL, intr);
	spin_unlock_irqrestore(&msm_host->intr_lock, flags);
}