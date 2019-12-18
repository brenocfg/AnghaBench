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
typedef  int /*<<< orphan*/  u8 ;
struct t7l66xb {int /*<<< orphan*/  clk32k; int /*<<< orphan*/  lock; scalar_t__ scr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ SCR_DEV_CTL ; 
 int /*<<< orphan*/  SCR_DEV_CTL_MMC ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct t7l66xb* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int t7l66xb_mmc_disable(struct platform_device *mmc)
{
	struct t7l66xb *t7l66xb = dev_get_drvdata(mmc->dev.parent);
	unsigned long flags;
	u8 dev_ctl;

	raw_spin_lock_irqsave(&t7l66xb->lock, flags);

	dev_ctl = tmio_ioread8(t7l66xb->scr + SCR_DEV_CTL);
	dev_ctl &= ~SCR_DEV_CTL_MMC;
	tmio_iowrite8(dev_ctl, t7l66xb->scr + SCR_DEV_CTL);

	raw_spin_unlock_irqrestore(&t7l66xb->lock, flags);

	clk_disable_unprepare(t7l66xb->clk32k);

	return 0;
}