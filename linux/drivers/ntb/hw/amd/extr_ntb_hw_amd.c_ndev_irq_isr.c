#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct amd_ntb_dev {TYPE_2__ ntb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndev_interrupt (struct amd_ntb_dev*,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ndev_irq_isr(int irq, void *dev)
{
	struct amd_ntb_dev *ndev = dev;

	return ndev_interrupt(ndev, irq - ndev->ntb.pdev->irq);
}