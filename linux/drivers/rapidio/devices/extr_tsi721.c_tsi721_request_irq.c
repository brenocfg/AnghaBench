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
struct tsi721_device {int flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int TSI721_USING_MSI ; 
 int TSI721_USING_MSIX ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tsi721_irqhandler ; 
 int tsi721_request_msix (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int tsi721_request_irq(struct tsi721_device *priv)
{
	int err;

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX)
		err = tsi721_request_msix(priv);
	else
#endif
		err = request_irq(priv->pdev->irq, tsi721_irqhandler,
			  (priv->flags & TSI721_USING_MSI) ? 0 : IRQF_SHARED,
			  DRV_NAME, (void *)priv);

	if (err)
		tsi_err(&priv->pdev->dev,
			"Unable to allocate interrupt, err=%d", err);

	return err;
}