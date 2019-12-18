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
struct tsi721_device {int flags; TYPE_2__* pdev; TYPE_1__* msix; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int TSI721_USING_MSIX ; 
 size_t TSI721_VECT_IDB ; 
 size_t TSI721_VECT_PWRX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void tsi721_free_irq(struct tsi721_device *priv)
{
#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX) {
		free_irq(priv->msix[TSI721_VECT_IDB].vector, (void *)priv);
		free_irq(priv->msix[TSI721_VECT_PWRX].vector, (void *)priv);
	} else
#endif
	free_irq(priv->pdev->irq, (void *)priv);
}