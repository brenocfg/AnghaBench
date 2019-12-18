#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qib_devdata {int flags; int num_pports; TYPE_4__* cspec; TYPE_3__* pport; TYPE_1__* pcidev; } ;
struct TYPE_8__ {int dca_ctrl; int gpio_mask; int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  msix_entries; int /*<<< orphan*/  sendibchk; int /*<<< orphan*/  sendgrhchk; int /*<<< orphan*/  sendchkenable; int /*<<< orphan*/  cntrs; } ;
struct TYPE_7__ {TYPE_2__* cpspec; } ;
struct TYPE_6__ {int /*<<< orphan*/  portcntrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACtrlA ; 
 int /*<<< orphan*/  KREG_IDX (int /*<<< orphan*/ ) ; 
 int QIB_DCA_ENABLED ; 
 int QIB_HAS_QSFP ; 
 int QSFP_GPIO_MOD_PRS_N ; 
 int QSFP_GPIO_PORT2_SHIFT ; 
 int /*<<< orphan*/  dca_remove_requester (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_gpio_mask ; 
 int /*<<< orphan*/  qib_7322_free_irq (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_setup_7322_cleanup(struct qib_devdata *dd)
{
	int i;

#ifdef CONFIG_INFINIBAND_QIB_DCA
	if (dd->flags & QIB_DCA_ENABLED) {
		dca_remove_requester(&dd->pcidev->dev);
		dd->flags &= ~QIB_DCA_ENABLED;
		dd->cspec->dca_ctrl = 0;
		qib_write_kreg(dd, KREG_IDX(DCACtrlA), dd->cspec->dca_ctrl);
	}
#endif

	qib_7322_free_irq(dd);
	kfree(dd->cspec->cntrs);
	kfree(dd->cspec->sendchkenable);
	kfree(dd->cspec->sendgrhchk);
	kfree(dd->cspec->sendibchk);
	kfree(dd->cspec->msix_entries);
	for (i = 0; i < dd->num_pports; i++) {
		unsigned long flags;
		u32 mask = QSFP_GPIO_MOD_PRS_N |
			(QSFP_GPIO_MOD_PRS_N << QSFP_GPIO_PORT2_SHIFT);

		kfree(dd->pport[i].cpspec->portcntrs);
		if (dd->flags & QIB_HAS_QSFP) {
			spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
			dd->cspec->gpio_mask &= ~mask;
			qib_write_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
			spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
		}
	}
}