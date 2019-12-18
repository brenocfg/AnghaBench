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
struct jme_adapter {TYPE_1__* pdev; TYPE_2__* dev; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_MSI ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_free_irq(struct jme_adapter *jme)
{
	free_irq(jme->pdev->irq, jme->dev);
	if (test_bit(JME_FLAG_MSI, &jme->flags)) {
		pci_disable_msi(jme->pdev);
		clear_bit(JME_FLAG_MSI, &jme->flags);
		jme->dev->irq = jme->pdev->irq;
	}
}