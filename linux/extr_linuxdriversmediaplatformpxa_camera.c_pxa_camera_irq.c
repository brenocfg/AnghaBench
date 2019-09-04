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
struct pxa_camera_dev {int /*<<< orphan*/  task_eof; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CICR0 ; 
 unsigned long CICR0_EOFM ; 
 scalar_t__ CISR ; 
 unsigned long CISR_EOF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pxa_camera_irq(int irq, void *data)
{
	struct pxa_camera_dev *pcdev = data;
	unsigned long status, cicr0;

	status = __raw_readl(pcdev->base + CISR);
	dev_dbg(pcdev_to_dev(pcdev),
		"Camera interrupt status 0x%lx\n", status);

	if (!status)
		return IRQ_NONE;

	__raw_writel(status, pcdev->base + CISR);

	if (status & CISR_EOF) {
		cicr0 = __raw_readl(pcdev->base + CICR0) | CICR0_EOFM;
		__raw_writel(cicr0, pcdev->base + CICR0);
		tasklet_schedule(&pcdev->task_eof);
	}

	return IRQ_HANDLED;
}