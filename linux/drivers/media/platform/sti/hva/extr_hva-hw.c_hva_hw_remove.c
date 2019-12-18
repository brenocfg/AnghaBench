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
struct hva_dev {int /*<<< orphan*/  irq_err; int /*<<< orphan*/  irq_its; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct device* hva_to_dev (struct hva_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 

void hva_hw_remove(struct hva_dev *hva)
{
	struct device *dev = hva_to_dev(hva);

	disable_irq(hva->irq_its);
	disable_irq(hva->irq_err);

	pm_runtime_put_autosuspend(dev);
	pm_runtime_disable(dev);
}