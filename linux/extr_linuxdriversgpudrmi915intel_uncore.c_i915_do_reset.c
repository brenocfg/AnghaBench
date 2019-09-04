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
 int /*<<< orphan*/  GRDOM_RESET_ENABLE ; 
 int /*<<< orphan*/  I915_GDRST ; 
 int i915_in_reset (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static int i915_do_reset(struct drm_i915_private *dev_priv, unsigned engine_mask)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int err;

	/* Assert reset for at least 20 usec, and wait for acknowledgement. */
	pci_write_config_byte(pdev, I915_GDRST, GRDOM_RESET_ENABLE);
	usleep_range(50, 200);
	err = wait_for(i915_in_reset(pdev), 500);

	/* Clear the reset request. */
	pci_write_config_byte(pdev, I915_GDRST, 0);
	usleep_range(50, 200);
	if (!err)
		err = wait_for(!i915_in_reset(pdev), 500);

	return err;
}