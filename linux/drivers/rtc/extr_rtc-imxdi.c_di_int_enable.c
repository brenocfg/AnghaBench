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
struct imxdi_dev {int /*<<< orphan*/  irq_lock; scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ DIER ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void di_int_enable(struct imxdi_dev *imxdi, u32 intr)
{
	unsigned long flags;

	spin_lock_irqsave(&imxdi->irq_lock, flags);
	writel(readl(imxdi->ioaddr + DIER) | intr,
	       imxdi->ioaddr + DIER);
	spin_unlock_irqrestore(&imxdi->irq_lock, flags);
}