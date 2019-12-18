#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnx2x {int flags; TYPE_3__* dev; TYPE_2__* pdev; TYPE_1__* msix_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {unsigned int irq; } ;
struct TYPE_4__ {unsigned int vector; } ;

/* Variables and functions */
 unsigned long IRQF_SHARED ; 
 int USING_MSIX_FLAG ; 
 int USING_MSI_FLAG ; 
 int /*<<< orphan*/  bnx2x_interrupt ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int bnx2x_req_irq(struct bnx2x *bp)
{
	unsigned long flags;
	unsigned int irq;

	if (bp->flags & (USING_MSI_FLAG | USING_MSIX_FLAG))
		flags = 0;
	else
		flags = IRQF_SHARED;

	if (bp->flags & USING_MSIX_FLAG)
		irq = bp->msix_table[0].vector;
	else
		irq = bp->pdev->irq;

	return request_irq(irq, bnx2x_interrupt, flags, bp->dev->name, bp->dev);
}