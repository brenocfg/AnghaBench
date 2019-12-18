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
typedef  int u32 ;
struct udc {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_irqmsk; int /*<<< orphan*/  irqmsk; } ;

/* Variables and functions */
 int AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_DEVINT_ENUM ; 
 int /*<<< orphan*/  UDC_DEVINT_ES ; 
 int /*<<< orphan*/  UDC_DEVINT_SC ; 
 int /*<<< orphan*/  UDC_DEVINT_SI ; 
 int /*<<< orphan*/  UDC_DEVINT_SOF ; 
 int /*<<< orphan*/  UDC_DEVINT_SVC ; 
 int /*<<< orphan*/  UDC_DEVINT_UR ; 
 int /*<<< orphan*/  UDC_DEVINT_US ; 
 int UDC_EPINT_MSK_DISABLE_ALL ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

int udc_mask_unused_interrupts(struct udc *dev)
{
	u32 tmp;

	/* mask all dev interrupts */
	tmp =	AMD_BIT(UDC_DEVINT_SVC) |
		AMD_BIT(UDC_DEVINT_ENUM) |
		AMD_BIT(UDC_DEVINT_US) |
		AMD_BIT(UDC_DEVINT_UR) |
		AMD_BIT(UDC_DEVINT_ES) |
		AMD_BIT(UDC_DEVINT_SI) |
		AMD_BIT(UDC_DEVINT_SOF)|
		AMD_BIT(UDC_DEVINT_SC);
	writel(tmp, &dev->regs->irqmsk);

	/* mask all ep interrupts */
	writel(UDC_EPINT_MSK_DISABLE_ALL, &dev->regs->ep_irqmsk);

	return 0;
}