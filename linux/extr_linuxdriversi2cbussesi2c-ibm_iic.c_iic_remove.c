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
struct platform_device {int dummy; } ;
struct ibm_iic_private {int /*<<< orphan*/  vaddr; scalar_t__ irq; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct ibm_iic_private*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iic_interrupt_mode (struct ibm_iic_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ibm_iic_private*) ; 
 struct ibm_iic_private* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int iic_remove(struct platform_device *ofdev)
{
	struct ibm_iic_private *dev = platform_get_drvdata(ofdev);

	i2c_del_adapter(&dev->adap);

	if (dev->irq) {
		iic_interrupt_mode(dev, 0);
		free_irq(dev->irq, dev);
	}

	iounmap(dev->vaddr);
	kfree(dev);

	return 0;
}