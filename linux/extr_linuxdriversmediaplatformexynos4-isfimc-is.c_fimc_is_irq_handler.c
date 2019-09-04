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
typedef  unsigned long u32 ;
struct fimc_is {int /*<<< orphan*/  slock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long FIMC_IS_INT_FRAME_DONE_ISP ; 
 unsigned long FIMC_IS_INT_GENERAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MCUCTL_REG_INTSR1 ; 
 int /*<<< orphan*/  fimc_is_general_irq_handler (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_isp_irq_handler (struct fimc_is*) ; 
 unsigned long mcuctl_read (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t fimc_is_irq_handler(int irq, void *priv)
{
	struct fimc_is *is = priv;
	unsigned long flags;
	u32 status;

	spin_lock_irqsave(&is->slock, flags);
	status = mcuctl_read(is, MCUCTL_REG_INTSR1);

	if (status & (1UL << FIMC_IS_INT_GENERAL))
		fimc_is_general_irq_handler(is);

	if (status & (1UL << FIMC_IS_INT_FRAME_DONE_ISP))
		fimc_isp_irq_handler(is);

	spin_unlock_irqrestore(&is->slock, flags);
	return IRQ_HANDLED;
}