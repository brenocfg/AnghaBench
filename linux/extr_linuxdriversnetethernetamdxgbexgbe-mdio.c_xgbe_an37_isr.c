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
struct xgbe_prv_data {unsigned int an_int; unsigned int an_status; TYPE_1__* vdata; int /*<<< orphan*/  an_irq_work; int /*<<< orphan*/  an_workqueue; } ;
struct TYPE_2__ {scalar_t__ irq_reissue_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  MDIO_VEND2_AN_STAT ; 
 unsigned int XGBE_AN_CL37_INT_MASK ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XP_INT_REISSUE_EN ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_an37_disable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an37_enable_interrupts (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_an37_isr(struct xgbe_prv_data *pdata)
{
	unsigned int reg;

	/* Disable AN interrupts */
	xgbe_an37_disable_interrupts(pdata);

	/* Save the interrupt(s) that fired */
	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
	pdata->an_int = reg & XGBE_AN_CL37_INT_MASK;
	pdata->an_status = reg & ~XGBE_AN_CL37_INT_MASK;

	if (pdata->an_int) {
		/* Clear the interrupt(s) that fired and process them */
		reg &= ~XGBE_AN_CL37_INT_MASK;
		XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, reg);

		queue_work(pdata->an_workqueue, &pdata->an_irq_work);
	} else {
		/* Enable AN interrupts */
		xgbe_an37_enable_interrupts(pdata);

		/* Reissue interrupt if status is not clear */
		if (pdata->vdata->irq_reissue_support)
			XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 3);
	}
}