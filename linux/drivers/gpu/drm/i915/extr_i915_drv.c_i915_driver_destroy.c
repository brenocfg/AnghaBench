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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_driver_destroy(struct drm_i915_private *i915)
{
	struct pci_dev *pdev = i915->drm.pdev;

	drm_dev_fini(&i915->drm);
	kfree(i915);

	/* And make sure we never chase our dangling pointer from pci_dev */
	pci_set_drvdata(pdev, NULL);
}