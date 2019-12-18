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
struct xgbe_prv_data {int an_int; TYPE_1__* vdata; int /*<<< orphan*/  an_irq_work; int /*<<< orphan*/  an_workqueue; } ;
struct TYPE_2__ {scalar_t__ irq_reissue_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_INT ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XP_INT_REISSUE_EN ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_an73_disable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an73_enable_interrupts (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_an73_isr(struct xgbe_prv_data *pdata)
{
	/* Disable AN interrupts */
	xgbe_an73_disable_interrupts(pdata);

	/* Save the interrupt(s) that fired */
	pdata->an_int = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_INT);

	if (pdata->an_int) {
		/* Clear the interrupt(s) that fired and process them */
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, ~pdata->an_int);

		queue_work(pdata->an_workqueue, &pdata->an_irq_work);
	} else {
		/* Enable AN interrupts */
		xgbe_an73_enable_interrupts(pdata);

		/* Reissue interrupt if status is not clear */
		if (pdata->vdata->irq_reissue_support)
			XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 3);
	}
}