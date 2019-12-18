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
struct pci_dev {int dummy; } ;
struct intel_gt {TYPE_2__* i915; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRDOM_RESET_ENABLE ; 
 int /*<<< orphan*/  I915_GDRST ; 
 int /*<<< orphan*/  g4x_reset_complete (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_atomic (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int g33_do_reset(struct intel_gt *gt,
			intel_engine_mask_t engine_mask,
			unsigned int retry)
{
	struct pci_dev *pdev = gt->i915->drm.pdev;

	pci_write_config_byte(pdev, I915_GDRST, GRDOM_RESET_ENABLE);
	return wait_for_atomic(g4x_reset_complete(pdev), 50);
}